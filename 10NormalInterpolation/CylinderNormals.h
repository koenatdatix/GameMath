#pragma once
#include "pch.h"
#include "Mesh.h"

namespace gm
{
	class CylinderNormals final
		: public Mesh
	{
	public:
		explicit CylinderNormals(float radius = .5f, float height = 1.f, uint32_t segmentCount = 16);
	private:
		float mRadius;
		float mHeight;
		uint32_t mSegmentCount;
	};
}
