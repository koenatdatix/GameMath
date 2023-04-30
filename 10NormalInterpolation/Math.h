#pragma once
#include "pch.h"

namespace gm
{
	std::array<float, 4> MatrixMultiply(const std::array<float, 16>& matrix, const std::array<float, 4>& vertex);
	std::array<float, 4> MatrixMultiply(const std::array<float, 4>& vertex, const std::array<float, 16>& matrix);
	std::array<float, 16> MatrixMultiply(const std::array<float, 16>& matrix1, const std::array<float, 16>& matrix2);
	float Dot(const std::array<float, 4>& a, const std::array<float, 4>& b);
	std::array<float, 4> Cross(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2);
	std::array<float, 4> Normalize(const std::array<float, 4>& vertex);
	std::array<float, 4> VertexMultiply(const std::array<float, 4>& vertex, const float& scalar);
	std::array<float, 4> VertexAdd(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2);
	std::array<float, 4> VertexSubtract(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2);
	std::array<float, 4> Middle(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2, const std::array<float, 4>& vertex3);
	std::array<float, 16> MatrixInverse(const std::array<float, 16>& m);
	std::array<float, 4> CreateQuaternion(float angle, float x, float y, float z);
	std::array<float, 4> QuaternionMultiply(const std::array<float, 4>& quat1, const std::array<float, 4>& quat2);
	std::array<float, 4> QuaternionRotate(const std::array<float, 4>& quat1, const std::array<float, 4>& quat2);
	std::array<float, 4> QuaternionCross(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2);
}
