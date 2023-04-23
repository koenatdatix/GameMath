#pragma once
#include "Mesh.h"

namespace gm
{
	class Cylinder final
		: public Mesh
	{
	public:
		explicit Cylinder(float radius = .5f, float height = 1.f, uint32_t segmentCount = 16);
	private:
		float mRadius;
		float mHeight;
		uint32_t mSegmentCount;
	};
}
