#include "MovingCamera.h"
#include "Math.h"

gm::MovingCamera::MovingCamera(uint32_t width, uint32_t height)
	: Camera(width, height)
{
}

void gm::MovingCamera::Move([[maybe_unused]] const float duration, const gm::MouseButton mouseButton, const POINT& pos)
{
	bool hasMoved{ false };
	switch (mouseButton)
	{
	case gm::MouseButton::Left:
		mPosition[0] -= float(pos.x);
		mPosition[1] += float(pos.y);
		hasMoved = true;
		break;
	case gm::MouseButton::Middle:
		mPosition[2] += float(pos.y);
		hasMoved = true;
		break;
	case gm::MouseButton::Right:
		std::array<float, 4>
			quat{},
			right{ 0.f, mRight[0], mRight[1], mRight[2] },
			up{ 0.f, mUp[0], mUp[1], mUp[2] },
			lookAt{ 0.f, mLookAt[0], mLookAt[1], mLookAt[2] };
		quat = gm::CreateQuaternion(float(pos.x) / 100.f, mUp[0], mUp[1], mUp[2]);
		right = gm::Normalize(gm::QuaternionRotate(quat, right));
		lookAt = gm::Normalize(gm::QuaternionRotate(quat, lookAt));
		quat = gm::CreateQuaternion(float(pos.y) / 100.f, mRight[0], mRight[1], mRight[2]);
		up = gm::Normalize(gm::QuaternionRotate(quat, up));
		lookAt = gm::Normalize(gm::QuaternionRotate(quat, lookAt));
		mRight = { right[1], right[2], right[3], 0.f };
		mUp = { up[1], up[2], up[3], 0.f };
		mLookAt = { lookAt[1], lookAt[2], lookAt[3], 0.f };
		hasMoved = true;
		break;
	}
	if (hasMoved)
		Camera::CalcViewProj();
}
