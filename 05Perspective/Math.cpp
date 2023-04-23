#include "Math.h"

std::array<float, 4> gm::MatrixMultiply(const std::array<float, 16>& matrix, const std::array<float, 4>& vertex)
{
	std::array<float, 4> result{};
	result[0] = matrix[0] * vertex[0] + matrix[1] * vertex[1] + matrix[2] * vertex[2] + matrix[3] * vertex[3];
	result[1] = matrix[4] * vertex[0] + matrix[5] * vertex[1] + matrix[6] * vertex[2] + matrix[7] * vertex[3];
	result[2] = matrix[8] * vertex[0] + matrix[9] * vertex[1] + matrix[10] * vertex[2] + matrix[11] * vertex[3];
	result[3] = matrix[12] * vertex[0] + matrix[13] * vertex[1] + matrix[14] * vertex[2] + matrix[15] * vertex[3];
	return result;
}

std::array<float, 4> gm::MatrixMultiply(const std::array<float, 4>& vertex, const std::array<float, 16>& matrix)
{
	std::array<float, 4> result{};
	result[0] = matrix[0] * vertex[0] + matrix[4] * vertex[1] + matrix[8] * vertex[2] + matrix[12] * vertex[3];
	result[1] = matrix[1] * vertex[0] + matrix[5] * vertex[1] + matrix[9] * vertex[2] + matrix[13] * vertex[3];
	result[2] = matrix[2] * vertex[0] + matrix[6] * vertex[1] + matrix[10] * vertex[2] + matrix[14] * vertex[3];
	result[3] = matrix[3] * vertex[0] + matrix[7] * vertex[1] + matrix[11] * vertex[2] + matrix[15] * vertex[3];
	return result;
}

std::array<float, 16> gm::MatrixMultiply(const std::array<float, 16>& matrix1, const std::array<float, 16>& matrix2)
{
	std::array<float, 16> result{};
	for (uint64_t row{ 0 }; row < 4; ++row)
		for (uint64_t col{ 0 }; col < 4; ++col)
			result[row * 4 + col] =
			matrix1[row * 4] * matrix2[col] +
			matrix1[row * 4 + 1] * matrix2[1 * 4 + col] +
			matrix1[row * 4 + 2] * matrix2[2 * 4 + col] +
			matrix1[row * 4 + 3] * matrix2[3 * 4 + col];
	return result;
}

float gm::Dot(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2)
{
	return vertex1[0] * vertex2[0] + vertex1[1] * vertex2[1] + vertex1[2] * vertex2[2];
}

std::array<float, 4> gm::Cross(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2)
{
	std::array<float, 4> result{};
	result[0] = vertex1[1] * vertex2[2] - vertex1[2] * vertex2[1];
	result[1] = vertex1[2] * vertex2[0] - vertex1[0] * vertex2[2];
	result[2] = vertex1[0] * vertex2[1] - vertex1[1] * vertex2[0];
	result[3] = 0.f;
	return result;
}

std::array<float, 4> gm::Normalize(const std::array<float, 4>& vertex)
{
	float length{ std::sqrt(vertex[0] * vertex[0] + vertex[1] * vertex[1] + vertex[2] * vertex[2] + vertex[3] * vertex[3]) };
	std::array<float, 4> result{};
	result[0] = vertex[0] / length;
	result[1] = vertex[1] / length;
	result[2] = vertex[2] / length;
	result[3] = vertex[3] / length;
	return result;
}

std::array<float, 4> gm::VertexMultiply(const std::array<float, 4>& vertex, const float& scalar)
{
	return std::array<float, 4>{ vertex[0] * scalar, vertex[1] * scalar, vertex[2] * scalar, vertex[3] * scalar};
}

std::array<float, 4> gm::VertexAdd(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2)
{
	return std::array<float, 4>{ vertex1[0] + vertex2[0], vertex1[1] + vertex2[1], vertex1[2] + vertex2[2], vertex1[3] + vertex2[3]};
}

std::array<float, 4> gm::VertexSubtract(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2)
{
	return std::array<float, 4>{ vertex1[0] - vertex2[0], vertex1[1] - vertex2[1], vertex1[2] - vertex2[2], vertex1[3] - vertex2[3]};
}

std::array<float, 4> gm::Middle(const std::array<float, 4>& vertex1, const std::array<float, 4>& vertex2, const std::array<float, 4>& vertex3)
{
	std::array<float, 4> result{};
	result[0] = (vertex1[0] + vertex2[0] + vertex3[0]) / 3.f;
	result[1] = (vertex1[1] + vertex2[1] + vertex3[1]) / 3.f;
	result[2] = (vertex1[2] + vertex2[2] + vertex3[2]) / 3.f;
	result[3] = 0.f;
	return result;
}

std::array<float, 16> gm::MatrixInverse(const std::array<float, 16>& m)
{
	std::array<float, 16> inv{};
	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	float det{ m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12] };
	if (det == 0)
		return inv;
	det = 1.0f / det;
	for (uint64_t i{ 0 }; i < 16; i++)
		inv[i] = inv[i] * det;
	return inv;
}
