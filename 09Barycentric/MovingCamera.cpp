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
		mPosition = gm::VertexSubtract(mPosition, gm::VertexMultiply(mRight, float(pos.x)));
		mPosition = gm::VertexAdd(mPosition, gm::VertexMultiply(mUp, float(pos.y)));
		hasMoved = true;
		break;
	case gm::MouseButton::Middle:
		mPosition = gm::VertexAdd(mPosition, gm::VertexMultiply(mLookAt, float(pos.y)));
		hasMoved = true;
		break;
	case gm::MouseButton::Right:
		std::array<float, 4>
			quat{},
			qRight{ 0.f, mRight[0], mRight[1], mRight[2] },
			qUp{ 0.f, mUp[0], mUp[1], mUp[2] },
			qLookAt{ 0.f, mLookAt[0], mLookAt[1], mLookAt[2] };
		quat = gm::CreateQuaternion(float(pos.x) / 500.f, mUp[0], mUp[1], mUp[2]);
		qLookAt = gm::Normalize(gm::QuaternionRotate(quat, qLookAt));
		quat = gm::CreateQuaternion(float(pos.y) / 500.f, mRight[0], mRight[1], mRight[2]);
		qLookAt = gm::Normalize(gm::QuaternionRotate(quat, qLookAt));
		qRight = gm::Normalize(gm::QuaternionCross(std::array<float, 4>{ 0.f, 0.f, 1.f, 0.f }, qLookAt));
		qUp = gm::Normalize((gm::QuaternionCross(qLookAt, qRight)));
		mRight = { qRight[1], qRight[2], qRight[3], 0.f };
		mUp = { qUp[1], qUp[2], qUp[3], 0.f };
		mLookAt = { qLookAt[1], qLookAt[2], qLookAt[3], 0.f };
		hasMoved = true;
		break;
	}
	if (hasMoved)
		Camera::CalcViewProj();
}
