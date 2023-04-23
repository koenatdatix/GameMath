#include "pch.h"
#include "Cylinder.h"

gm::Cylinder::Cylinder(float radius, float height, uint32_t segmentCount)
	: Mesh()
	, mRadius{ radius }
	, mHeight{ height }
	, mSegmentCount{ segmentCount }
{
	uint64_t cnt{ mSegmentCount };
	Mesh::mVertices.reserve(cnt * 2 + 2);
	Mesh::mTriangles.reserve(cnt * 4);
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, 0.f, 0.f, 1.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, mHeight, 0.f, 1.f });
	float
		x{}, z{},
		totalAngle{ 0.f },
		segmentAngle{ 2.f * std::numbers::pi_v<float> / float(cnt) };
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	uint64_t
		oldBottom{ 2 }, oldTop{ 3 },
		newBottom{ 4 }, newTop{ 5 };
	for (uint64_t i{ 1 }; i < cnt; ++i)
	{
		totalAngle += segmentAngle;
		x = std::cos(totalAngle) * mRadius;
		z = std::sin(totalAngle) * mRadius;
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 0, newBottom, oldBottom });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 1, oldTop, newTop });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldBottom, newBottom, oldTop });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldTop, newBottom, newTop });
		oldBottom += 2;
		oldTop += 2;
		newBottom += 2;
		newTop += 2;
	}
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 0, 2, oldBottom });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 1, oldTop, 3 });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldBottom, 2, oldTop });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldTop, 2, 3 });
}
