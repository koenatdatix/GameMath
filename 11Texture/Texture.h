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
		std::array<float, 4> GetPixelColor(int u, int v) const;
		std::array<float, 4> SampleBilinear(float u, float v) const;
		//std::array<float, 4> SampleAnisotropic(float u, float v, float du_dx, float du_dy, float dv_dx, float dv_dy);
	private:
		UINT
			mWidth,
			mHeight;
		BYTE* mpPixelData;
	};
}
