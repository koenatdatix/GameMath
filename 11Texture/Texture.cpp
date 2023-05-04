#include "Texture.h"

gm::Texture::Texture(const std::wstring& filename)
	: mWidth{}
	, mHeight{}
	, mpPixelData{ nullptr }
{
	IWICImagingFactory* pFactory{ nullptr };
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
	if (!SUCCEEDED(hr))
		return;
	IWICBitmapDecoder* pBitmapDecoder;
	hr = pFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pBitmapDecoder);
	if (!SUCCEEDED(hr))
		return;
	IWICBitmapFrameDecode* pBitmapSource;
	hr = pBitmapDecoder->GetFrame(0, &pBitmapSource);
	if (!SUCCEEDED(hr))
		return;
	//WICPixelFormatGUID pixelFormat{};
	//pBitmapSource->GetPixelFormat(&pixelFormat);
	pBitmapSource->GetSize(&mWidth, &mHeight);
	mpPixelData = new BYTE[mWidth * mHeight * 3];
	WICRect wicRect{ 0, 0, INT(mWidth), INT(mHeight) };
	pBitmapSource->CopyPixels(&wicRect, mWidth * 3, mWidth * mHeight * 3, mpPixelData);
	SafeRelease(&pBitmapSource);
	SafeRelease(&pBitmapDecoder);
	SafeRelease(&pFactory);
}

gm::Texture::~Texture()
{
}

std::array<float, 4> gm::Texture::GetPixelColor(float u, float v) const
{
	if (mpPixelData == nullptr)
		return std::array<float, 4>{ 1.f, 1.f, 1.f, 0.f };
	BYTE pixelBGR[3]{};
	WICRect wicRect{ INT((float(mWidth) - .01f) * u), INT((float(mHeight) - .01f) * v), 1, 1 };
	pixelBGR[0] = mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3];
	pixelBGR[1] = mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3 + 1];
	pixelBGR[2] = mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3 + 2];
	return std::array<float, 4>{ float(pixelBGR[2]) / 255.f, float(pixelBGR[1]) / 255.f, float(pixelBGR[0]) / 255.f, 0.f };
}

std::array<float, 4> gm::Texture::GetPixelColor(int u, int v) const
{
    WICRect wicRect{ u, v, 1, 1 };
    BYTE pixelBGR[3]{
        mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3],
        mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3 + 1],
        mpPixelData[wicRect.Y * mWidth * 3 + wicRect.X * 3 + 2] };
    return std::array<float, 4>{ float(pixelBGR[2]) / 255.f, float(pixelBGR[1]) / 255.f, float(pixelBGR[0]) / 255.f, 0.f };
}

std::array<float, 4> gm::Texture::SampleBilinear(float u, float v) const
{
    if (mpPixelData == nullptr)
        return std::array<float, 4>{ 1.f, 1.f, 1.f, 0.f };
    // Convert texture coordinates from [0,1] range to [0, width-1] and [0, height-1] range
    float
        x{ u * float(mWidth - 1) },
        y{ v * float(mHeight - 1) };
    // Compute the integer coordinates of the four texels surrounding the given coordinates
    int
        x0{ std::clamp(int(std::floor(x)), 0, int(mWidth) - 1) },
        y0{ std::clamp(int(std::floor(y)), 0, int(mHeight) - 1) };
    int
        x1{ std::clamp(int(x0 + 1.f), 0, int(mWidth - 1)) },
        y1{ std::clamp(int(y0 + 1.f), 0, int(mHeight - 1)) };
    // Compute the fractional part of the texture coordinates
    float
        x_frac{ x - float(x0) },
        y_frac{ y - float(y0) };
    // Sample the four texels surrounding the given coordinates
    std::array<float, 4>
        texel00{ GetPixelColor(x0, y0) },
        texel01{ GetPixelColor(x0, y1) },
        texel10{ GetPixelColor(x1, y0) },
        texel11{ GetPixelColor(x1, y1) };
    // Compute the bilinearly interpolated value
    std::array<float, 4> interp0{}, interp1{}, interp{};
    for (int i{ 0 }; i < 3; ++i) {
        interp0[i] = texel00[i] * (1.0f - x_frac) + texel10[i] * x_frac;
        interp1[i] = texel01[i] * (1.0f - x_frac) + texel11[i] * x_frac;
        interp[i] = interp0[i] * (1.0f - y_frac) + interp1[i] * y_frac;
    }
    return interp;
}

//std::array<float, 4> gm::Texture::SampleAnisotropic(float u, float v, float du_dx, [[maybe_unused]] float du_dy, float dv_dx, [[maybe_unused]] float dv_dy)
//{
//    const float
//        max_anisotropy{ 16.0f },
//        threshold{ .1f },
//        initial_width{ 1.f };
//    const int max_iterations{ 4 };
//
//    std::array<float, 4> sum{ 0.0f, 0.0f, 0.0f, 0.0f };
//    float total_weight{ 0.f };
//    float width{ initial_width };
//    for (int i{ 0 }; i < max_iterations; i++)
//    {
//        float inv_width{ 1.f / width };
//        float du{ du_dx * inv_width };
//        float dv{ dv_dx * inv_width };
//        float max_delta{ std::max(std::abs(du), std::abs(dv)) * max_anisotropy };
//        float ds{ 1.f / std::sqrt(1.f + max_delta * max_delta) };
//        float s{ 0.f };
//        std::array<float, 4> prev_texel{ 0.0f, 0.0f, 0.0f, 0.0f };
//        bool first_iteration{ true };
//        while (s < 1.f) {
//            float uu{ u + du * s };
//            float vv{ v + dv * s };
//            std::array<float, 4> texel{ GetPixelColor(uu, vv) };
//            if (!first_iteration)
//            {
//                float weight{
//                    std::exp(-((texel[0] - prev_texel[0]) * (texel[0] - prev_texel[0]) +
//                    (texel[1] - prev_texel[1]) * (texel[1] - prev_texel[1]) +
//                    (texel[2] - prev_texel[2]) * (texel[2] - prev_texel[2])) /
//                    (2.f * threshold * threshold)) };
//                sum[0] += texel[0] * weight;
//                sum[1] += texel[1] * weight;
//                sum[2] += texel[2] * weight;
//                total_weight += weight;
//            }
//            prev_texel = texel;
//            s += ds;
//            first_iteration = false;
//        }
//        width *= 2.0f;
//    }
//    return std::array<float, 4>{ sum[0] / total_weight, sum[1] / total_weight, sum[2] / total_weight, 0.f };
//}
