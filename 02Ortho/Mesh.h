#pragma once
#include "pch.h"

namespace gm
{
	class Mesh
	{
	public:
		explicit Mesh();
		virtual ~Mesh() = default;

		virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush);
	protected:
		std::vector<std::array<float, 4>> mVertices;
		std::vector<std::array<uint64_t, 3>> mTriangles;
	private:
		void RenderTriangle(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
	};
}
