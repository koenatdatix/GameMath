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
