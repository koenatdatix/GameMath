#include "Mesh.h"
#include "Math.h"

const std::array<float, 16> gm::Mesh::mIdentityMatrix{
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

gm::Mesh::Mesh()
	: mVertices{}
	, mTriangles{}
	, mScale{ .5f }
	, mTranslation{ 0.f, 0.f, 0.f }
	, mRotation{ std::numbers::pi_v<float> / 6.f, 0.f, std::numbers::pi_v<float> / 6.f }
	, mHasMoved{ true }
	, mTransformedVertices{}
	, mObjectToWorldMatrix{}
{}

void gm::Mesh::Render(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush)
{
	if (mHasMoved)
	{
		mHasMoved = false;
		float c{}, s{};
		std::array<float, 16> r{};
		std::memcpy((void*)mObjectToWorldMatrix.data(), (void*)mIdentityMatrix.data(), 16 * sizeof(float));
		mObjectToWorldMatrix[0] = mScale;
		mObjectToWorldMatrix[5] = mScale;
		mObjectToWorldMatrix[10] = mScale;
		c = std::cos(mRotation[0]);
		s = std::sin(mRotation[0]);
		r = std::array<float, 16>{
			1.f, 0.f, 0.f, 0.f,
			0.f,   c,   s, 0.f,
			0.f,  -s,   c, 0.f,
			0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		c = std::cos(mRotation[1]);
		s = std::sin(mRotation[1]);
		r = std::array<float, 16>{
			  c, 0.f,  -s, 0.f,
			0.f, 1.f, 0.f, 0.f,
			  s, 0.f,   c, 0.f,
			0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		c = std::cos(mRotation[2]);
		s = std::sin(mRotation[2]);
		r = std::array<float, 16>{
			  c,   s, 0.f, 0.f,
			 -s,   c, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		std::memcpy((void*)r.data(), (void*)mIdentityMatrix.data(), 16 * sizeof(float));
		r[12] = mTranslation[0];
		r[13] = mTranslation[1];
		r[14] = mTranslation[2];
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		mTransformedVertices.clear();
		mTransformedVertices.reserve(mVertices.size());
		for (auto& vertex : mVertices)
			mTransformedVertices.emplace_back(gm::MatrixMultiply(vertex, mObjectToWorldMatrix));
	}
	for (auto& triangle : mTriangles)
		RenderTriangle(
			pRenderTarget,
			pSolidColorBrush,
			mTransformedVertices[triangle[0]],
			mTransformedVertices[triangle[1]],
			mTransformedVertices[triangle[2]]
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
