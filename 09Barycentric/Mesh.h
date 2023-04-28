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

		virtual void Move(const float duration, const gm::MouseButton mouseButton, const POINT& pos);
		virtual void Render(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush);
	protected:
		std::vector<std::array<float, 4>> mVertices;
		std::vector<std::array<uint64_t, 3>> mTriangles;
		float mScale;
		std::array<float, 3> mTranslation;
		std::array<float, 3> mRotation;
	private:
		bool mHasMoved;
		std::vector<std::array<float, 4>> mWorldVertices;
		std::vector<std::array<float, 4>> mWvpVertices;
		std::array<float, 16> mObjectToWorldMatrix;
		std::vector<float> mDots;

		static const std::array<float, 16> mIdentityMatrix;

		void RenderTriangle(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
		void Rasterize(Window* pWindow, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
		bool InsideTriangle(const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3, const std::array<float, 4>& p);
		float EdgeFunction(const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& p);
	};
}
