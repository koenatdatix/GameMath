#include "Texture.h"

gm::Texture::Texture(const std::wstring& filename)
	: mpBitmapSource{ nullptr }
	, mWidth{}
	, mHeight{}
{
	IWICImagingFactory* pFactory{ nullptr };
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
	if (!SUCCEEDED(hr))
		return;
	IWICBitmapDecoder* pBitmapDecoder{ nullptr };
	hr = pFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pBitmapDecoder);
	if (!SUCCEEDED(hr))
		return;
	hr = pBitmapDecoder->GetFrame(0, &mpBitmapSource);
	if (!SUCCEEDED(hr))
		return;
	UINT width{}, height{};
	mpBitmapSource->GetSize(&width, &height);
	mWidth = float(width);
	mHeight = float(height);
}

std::array<float, 4> gm::Texture::GetPixelColor(float u, float v) const
{
	std::array<float, 4> pixel{};
	WICRect wicRect{ INT(mWidth * u), INT(mHeight * v), 1, 1 };
	mpBitmapSource->CopyPixels(&wicRect, 0, sizeof(pixel), (BYTE*)&pixel);
	return pixel;
}
