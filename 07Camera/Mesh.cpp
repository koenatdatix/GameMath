#include "Mesh.h"
#include "Window.h"
#include "Camera.h"
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
	, mScale{ 1.f }
	, mTranslation{ 0.f, 0.f, 0.f }
	, mRotation{ 0.f, 0.f, 0.f }
	, mHasMoved{ true }
	, mWorldVertices{}
	, mWvpVertices{}
	, mObjectToWorldMatrix{}
	, mDots{}
{}

void gm::Mesh::Move([[maybe_unused]] const float duration, const gm::MouseButton mouseButton, const POINT& pos)
{
	switch (mouseButton)
	{
	case gm::MouseButton::Left:
		mTranslation[0] -= float(pos.x);
		mTranslation[1] += float(pos.y);
		mHasMoved = true;
		break;
	case gm::MouseButton::Right:
		mRotation[0] += float(pos.y) / 180.f;
		mRotation[1] += float(pos.x) / 180.f;
		mHasMoved = true;
		break;
	case gm::MouseButton::Middle:
		mRotation[2] += float(pos.x) / 180.f;
		mHasMoved = true;
		break;
	}
}

void gm::Mesh::Render(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush)
{
	ID2D1HwndRenderTarget* pRenderTarget{ pWindow->GetRenderTarget() };
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
				0.f, c, s, 0.f,
				0.f, -s, c, 0.f,
				0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		c = std::cos(mRotation[1]);
		s = std::sin(mRotation[1]);
		r = std::array<float, 16>{
			c, 0.f, -s, 0.f,
				0.f, 1.f, 0.f, 0.f,
				s, 0.f, c, 0.f,
				0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		c = std::cos(mRotation[2]);
		s = std::sin(mRotation[2]);
		r = std::array<float, 16>{
			c, s, 0.f, 0.f,
				-s, c, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f };
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
		std::memcpy((void*)r.data(), (void*)mIdentityMatrix.data(), 16 * sizeof(float));
		r[12] = mTranslation[0];
		r[13] = mTranslation[1];
		r[14] = mTranslation[2];
		mObjectToWorldMatrix = gm::MatrixMultiply(mObjectToWorldMatrix, r);
	}
	Camera* pCamera{ pWindow->GetCamera() };
	std::array<float, 16> wvp{};
	wvp = gm::MatrixMultiply(mObjectToWorldMatrix, pCamera->GetViewInv());
	wvp = gm::MatrixMultiply(wvp, pCamera->GetProj());

	D2D1_SIZE_F size{ pRenderTarget->GetSize() };
	mWvpVertices.clear();
	mWvpVertices.reserve(mVertices.size());
	mWorldVertices.clear();
	mWorldVertices.reserve(mVertices.size());
	for (auto& vertex : mVertices)
	{
		mWorldVertices.emplace_back(gm::MatrixMultiply(vertex, mObjectToWorldMatrix));
		std::array<float, 4> v{ gm::MatrixMultiply(vertex, wvp) };
		v[0] /= v[3];
		v[1] /= v[3];
		v[2] /= v[3];
		v[0] *= (size.width / 2.f);
		v[1] *= (size.height / 2.f);
		mWvpVertices.emplace_back(v);
	}
	std::array<float, 4> camPos{};
	camPos = pCamera->GetPosition();
	mDots.clear();
	mDots.reserve(mTriangles.size());
	for (auto& triangle : mTriangles)
	{
		std::array<float, 4>
			p0{ mWorldVertices[triangle[0]] },
			p1{ mWorldVertices[triangle[1]] },
			p2{ mWorldVertices[triangle[2]] };
		std::array<float, 4>
			v0{ gm::VertexSubtract(p1, p0) },
			v1{ gm::VertexSubtract(p2, p0) };
		std::array<float, 4> middle{ Middle(p0, p1, p2) };
		mDots.emplace_back(
			gm::Dot(
				gm::Normalize(Cross(v0, v1)),
				gm::VertexSubtract(camPos, middle)
			)
		);
	}

	float zMin{ .96f };
	for (uint64_t i{ 0 }; i < mTriangles.size(); ++i)
		if ((mDots[i] <= 0.f) &&
			(mWvpVertices[mTriangles[i][0]][2] > zMin) &&
			(mWvpVertices[mTriangles[i][1]][2] > zMin) &&
			(mWvpVertices[mTriangles[i][2]][2] > zMin)
			)
			RenderTriangle(
				pRenderTarget,
				pSolidColorBrush,
				mWvpVertices[mTriangles[i][0]],
				mWvpVertices[mTriangles[i][1]],
				mWvpVertices[mTriangles[i][2]]
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
