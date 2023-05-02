#pragma once
#include "pch.h"

namespace gm
{
	class Texture final
	{
	public:
		explicit Texture(const std::wstring& filename);
		std::array<float, 4> GetPixelColor(float u, float v) const;
	private:
		IWICBitmapFrameDecode* mpBitmapSource;
		float
			mWidth,
			mHeight;
	};
}
