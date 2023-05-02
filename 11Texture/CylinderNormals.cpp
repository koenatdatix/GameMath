#include "CylinderNormals.h"

gm::CylinderNormals::CylinderNormals(float radius, float height, uint32_t segmentCount)
	: Mesh()
	, mRadius{ radius }
	, mHeight{ height }
	, mSegmentCount{ segmentCount }
{
	uint64_t cnt{ mSegmentCount };
	Mesh::mVertices.reserve(cnt * 2 + 2);
	Mesh::mTriangles.reserve(cnt * 4);
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
	float
		c{}, s{}, x{}, z{},
		totalAngle{ 0.f },
		segmentAngle{ 2.f * std::numbers::pi_v<float> / float(cnt) };
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	uint64_t
		oldBottomA{ 2 }, oldTopA{ 3 },
		newBottomA{ 6 }, newTopA{ 7 };
	uint64_t
		oldBottomB{ 4 }, oldTopB{ 5 },
		newBottomB{ 8 }, newTopB{ 9 };
	for (uint64_t i{ 1 }; i < cnt; ++i)
	{
		totalAngle += segmentAngle;
		c = std::cos(totalAngle);
		s = std::sin(totalAngle);
		x = c * mRadius;
		z = s * mRadius;
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ c, 0.f, s, 0.f });
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ c, 0.f, s, 0.f });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 0, newBottomA, oldBottomA });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 1, oldTopA, newTopA });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldBottomB, newBottomB, oldTopB });
		Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldTopB, newBottomB, newTopB });
		oldBottomA += 4;
		oldTopA += 4;
		newBottomA += 4;
		newTopA += 4;
		oldBottomB += 4;
		oldTopB += 4;
		newBottomB += 4;
		newTopB += 4;
	}
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 0, 2, oldBottomA });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 1, oldTopA, 3 });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldBottomB, 4, oldTopB });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldTopB, 4, 5 });
}
