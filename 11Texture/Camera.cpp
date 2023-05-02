#include "Camera.h"
#include "Math.h"

gm::Camera::Camera(uint32_t width, uint32_t height)
	: mView{}
	, mViewInv{}
	, mProj{}
	, mPosition{ 0.f, 0.f, -1000.f, 0.f }
	, mLookAt{ 0.f, 0.f, 1.f, 0.f }
	, mUp{ 0.f, 1.f, 0.f, 0.f }
	, mRight{ 1.f, 0.f, 0.f, 0.f }
	, mFov{ std::numbers::pi_v<float> / 3.f }
	, mAspectRatio{ float(width) / float(height) }
	, mNear{ 10.f }
	, mFar{ 5000.f }
{
	CalcViewProj();
}

std::array<float, 4>& gm::Camera::GetPosition()
{
	return mPosition;
}

std::array<float, 16>& gm::Camera::GetView()
{
	return mView;
}

std::array<float, 16>& gm::Camera::GetViewInv()
{
	return mViewInv;
}

std::array<float, 16>& gm::Camera::GetProj()
{
	return mProj;
}

void gm::Camera::CalcViewProj()
{
	mView = std::array<float, 16>{
		mRight[0], mRight[1], mRight[2], 0.f,
			mUp[0], mUp[1], mUp[2], 0.f,
			mLookAt[0], mLookAt[1], mLookAt[2], 0.f,
			mPosition[0], mPosition[1], mPosition[2], 1.f
	};
	//mViewInv = gm::MatrixInverse(mView);
	mViewInv = std::array<float, 16>{
		mRight[0], mUp[0], mLookAt[0], 0.f,
			mRight[1], mUp[1], mLookAt[1], 0.f,
			mRight[2], mUp[2], mLookAt[2], 0.f,
			-gm::Dot(mRight, mPosition), -gm::Dot(mUp, mPosition), -gm::Dot(mLookAt, mPosition), 1.f
	};
	float fovTan{ std::tan(mFov / 2.f) };
	mProj = std::array<float, 16>{
		1.f / (mAspectRatio * fovTan), 0.f, 0.f, 0.f,
			0.f, 1.f / fovTan, 0.f, 0.f,
			0.f, 0.f, mFar / (mFar - mNear), 1.f,
			0.f, 0.f, -(mNear * mFar) / (mFar - mNear), 0.f
	};
}

void gm::Camera::SetAspectRatio(uint32_t width, uint32_t height)
{
	mAspectRatio = float(width) / float(height);
	CalcViewProj();
}
