#pragma once
#include "pch.h"
#include "MouseButton.h"

namespace gm
{
	class Camera
	{
	public:
		explicit Camera(uint32_t width, uint32_t height);
		virtual ~Camera() = default;
		std::array<float, 4>& GetPosition();
		std::array<float, 16>& GetView();
		std::array<float, 16>& GetViewInv();
		std::array<float, 16>& GetProj();
		void CalcViewProj();
		void SetAspectRatio(uint32_t width, uint32_t height);
	protected:
		std::array<float, 16>
			mView,
			mViewInv,
			mProj;
		std::array<float, 4>
			mPosition,
			mLookAt,
			mUp,
			mRight;
		float
			mFov,
			mAspectRatio,
			mNear,
			mFar;
	};
}
