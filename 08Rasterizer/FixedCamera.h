#pragma once
#include "pch.h"
#include "Camera.h"

namespace gm
{
	class FixedCamera final
		: public Camera
	{
	public:
		explicit FixedCamera(uint32_t width, uint32_t height);
		virtual ~FixedCamera() = default;
		virtual void Move(const float duration, const gm::MouseButton mouseButton, const POINT& pos) override;
	};
}
