#include "Mesh.h"

gm::Mesh::Mesh()
	: mVertices{}
	, mTriangles{}
{}

void gm::Mesh::Render(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush)
{
	for (auto& triangle : mTriangles)
		RenderTriangle(
			pRenderTarget,
			pSolidColorBrush,
			mVertices[triangle[0]],
			mVertices[triangle[1]],
			mVertices[triangle[2]]
		);
}

void gm::Mesh::RenderTriangle(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3)
{
	D2D1_SIZE_F size{ pRenderTarget->GetSize() };
	float
		x{ float(size.width) / 2.f },
		y{ float(size.height) / 2.f };
	pRenderTarget->DrawLine(D2D1_POINT_2F{ v1[0] + x, y - v1[1] }, D2D1_POINT_2F{ v2[0] + x, y - v2[1] }, pSolidColorBrush);
	pRenderTarget->DrawLine(D2D1_POINT_2F{ v2[0] + x, y - v2[1] }, D2D1_POINT_2F{ v3[0] + x, y - v3[1] }, pSolidColorBrush);
	pRenderTarget->DrawLine(D2D1_POINT_2F{ v3[0] + x, y - v3[1] }, D2D1_POINT_2F{ v1[0] + x, y - v1[1] }, pSolidColorBrush);
}
