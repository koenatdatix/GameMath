#pragma once
#include "pch.h"
#include "MouseButton.h"

namespace gm
{
	class Window;

	class Mesh
	{
	public:
		explicit Mesh();
		virtual ~Mesh() = default;

		void SetTranslation(const std::array<float, 3>& translation);
		virtual void Move(const float duration, const gm::MouseButton mouseButton, const POINT& pos);
		virtual void Render(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush);
	protected:
		std::vector<std::array<float, 4>> mVertices;
		std::vector<std::array<float, 4>> mNormals;
		std::vector<std::array<uint64_t, 3>> mTriangles;
		float mScale;
		std::array<float, 3> mTranslation;
		std::array<float, 3> mRotation;
	private:
		bool mHasMoved;
		std::vector<std::array<float, 4>> mWorldVertices;
		std::vector<std::array<float, 4>> mWorldNormals;
		std::vector<std::array<float, 4>> mWvpVertices;
		std::array<float, 16> mObjectToWorldMatrix;
		std::vector<std::array<float, 4>> mFaceNormals;
		std::vector<float> mDots;

		static const std::array<float, 16> mIdentityMatrix;

		void RenderTriangle(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
		void Rasterize(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& n1, const std::array<float, 4>& v2, const std::array<float, 4>& n2, const std::array<float, 4>& v3, const std::array<float, 4>& n3);
		std::array<float, 3> Barycentric(const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3, const std::array<float, 4>& p);
	};
}
