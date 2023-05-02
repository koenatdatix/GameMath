#include "FixedCamera.h"

gm::FixedCamera::FixedCamera(uint32_t width, uint32_t height)
	: Camera(width, height)
{
}

void gm::FixedCamera::Move([[maybe_unused]] const float duration, [[maybe_unused]] const gm::MouseButton mouseButton, [[maybe_unused]] const POINT& pos)
{
}
