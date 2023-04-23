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
		float mScale;
		std::array<float, 3> mTranslation;
		std::array<float, 3> mRotation;
	private:
		bool mHasMoved;
		std::vector<std::array<float, 4>> mTransformedVertices;
		std::array<float, 16> mObjectToWorldMatrix;

		static const std::array<float, 16> mIdentityMatrix;

		void RenderTriangle(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pSolidColorBrush, const std::array<float, 4>& v1, const std::array<float, 4>& v2, const std::array<float, 4>& v3);
	};
}
