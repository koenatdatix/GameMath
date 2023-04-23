#pragma once
#include "pch.h"
#include "Camera.h"

namespace gm
{
	class MovingCamera final
		: public Camera
	{
	public:
		explicit MovingCamera(uint32_t width, uint32_t height);
		virtual ~MovingCamera() = default;
		virtual void Move(const float duration, const gm::MouseButton mouseButton, const POINT& pos) override;
	};
}
