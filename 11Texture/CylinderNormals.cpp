#include "CylinderNormals.h"

gm::CylinderNormals::CylinderNormals(float radius, float height, uint32_t segmentCount)
	: Mesh()
	, mRadius{ radius }
	, mHeight{ height }
	, mSegmentCount{ segmentCount }
{
	uint64_t cnt{ mSegmentCount };
	Mesh::mVertices.reserve(cnt * 4 + 2);
	Mesh::mTriangles.reserve(cnt * 4);
	// Middle Bottom
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 0.5f, 0.5f });
	// Middle Top
	Mesh::mVertices.emplace_back(std::array<float, 4>{ 0.f, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 0.5f, 0.5f });
	// Bottom
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, 0.5f });
	// Top
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, .5f });
	// Side Bottom
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 0.f, 0.f });
	// Side Top
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, 0.f });
	float
		c{}, s{}, x{}, z{},
		totalAngle{ 0.f },
		segmentAngle{ 2.f * std::numbers::pi_v<float> / float(cnt) };
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
		// Bottom
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
		Mesh::mUVs.emplace_back(std::array<float, 2>{ .5f + c / 2.f, .5f + s / 2.f });
		// Top
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
		Mesh::mUVs.emplace_back(std::array<float, 2>{ .5f + c / 2.f, .5f + s / 2.f });
		// Side Bottom
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, 0.f, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ c, 0.f, s, 0.f });
		Mesh::mUVs.emplace_back(std::array<float, 2>{ 0.f, float(i) / float(cnt) });
		// Side Top
		Mesh::mVertices.emplace_back(std::array<float, 4>{ x, mHeight, z, 1.f });
		Mesh::mNormals.emplace_back(std::array<float, 4>{ c, 0.f, s, 0.f });
		Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, float(i) / float(cnt) });

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

	// Bottom
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, -1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, .5f });
	// Top
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 0.f, 1.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, .5f });
	// Side Bottom
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, 0.f, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 0.f, 1.f });
	// Side Top
	Mesh::mVertices.emplace_back(std::array<float, 4>{ mRadius, mHeight, 0.f, 1.f });
	Mesh::mNormals.emplace_back(std::array<float, 4>{ 1.f, 0.f, 0.f, 0.f });
	Mesh::mUVs.emplace_back(std::array<float, 2>{ 1.f, 1.f });

	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 0, newBottomA, oldBottomA });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ 1, oldTopA, newTopA });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldBottomB, newBottomB, oldTopB });
	Mesh::mTriangles.emplace_back(std::array<uint64_t, 3>{ oldTopB, newBottomB, newTopB });
}
