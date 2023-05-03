#pragma once
#include "pch.h"

namespace gm
{
	class Texture final
	{
	public:
		explicit Texture(const std::wstring& filename);
		~Texture();
		std::array<float, 4> GetPixelColor(float u, float v) const;
	private:

		UINT
			mWidth,
			mHeight;
		BYTE* mpPixelData;
	};
}
