#pragma once
#include <cstdint>

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

struct v2i {
	i32 x, y;

	operator bool() const {
		return !(x == 0 && y == 0);
	}
};

struct v2 {
	float x, y;
};
struct v3 {
	float x, y, z;
};

struct v4 {
	float x, y, w, h;
};
struct v4i {
	i32 x, y, w, h;
};

struct col_t {
	i32 r, g, b, a;
	col_t() : r(0), g(0), b(0), a(0) { }
	col_t(i32 value, i32 alpha = 255) : r(value), g(value), b(value), a(alpha) { }
	col_t(i32 red, i32 green, i32 blue, i32 alpha) : r(red), g(green), b(blue), a(alpha) { }

	static col_t white() {
		return col_t{ 255, 255, 255, 255 };
	}
	static col_t black() {
		return col_t{ 0, 0, 0, 255 };
	}
};

struct mat3x4_t {
	float data[3][4]{ };
	float* operator[](i32 i) {
		return data[i];
	}

	const float* operator[](i32 i) const
	{
		return data[i];
	}

};
struct quaternion_t {
	float x{ }, y{ }, z{ }, w{ };
};

struct transform_t {
	v3 m_pos;
	quaternion_t m_rot;

	mat3x4_t to_matrix() {
		mat3x4_t m;
		m[0][0] = 1.0 - 2.0 * m_rot.y * m_rot.y - 2.0 * m_rot.z * m_rot.z;
		m[1][0] = 2.0 * m_rot.x * m_rot.y + 2.0 * m_rot.w * m_rot.z;
		m[2][0] = 2.0 * m_rot.x * m_rot.z - 2.0 * m_rot.w * m_rot.y;

		m[0][1] = 2.0f * m_rot.x * m_rot.y - 2.0f * m_rot.w * m_rot.z;
		m[1][1] = 1.0f - 2.0f * m_rot.x * m_rot.x - 2.0f * m_rot.z * m_rot.z;
		m[2][1] = 2.0f * m_rot.y * m_rot.z + 2.0f * m_rot.w * m_rot.x;

		m[0][2] = 2.0f * m_rot.x * m_rot.z + 2.0f * m_rot.w * m_rot.y;
		m[1][2] = 2.0f * m_rot.y * m_rot.z - 2.0f * m_rot.w * m_rot.x;
		m[2][2] = 1.0f - 2.0f * m_rot.x * m_rot.x - 2.0f * m_rot.y * m_rot.y;

		m[0][3] = m_pos.x;
		m[1][3] = m_pos.y;
		m[2][3] = m_pos.z;
		return m;
	}

};