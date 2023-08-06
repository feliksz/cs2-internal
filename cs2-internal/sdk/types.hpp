#pragma once
#include <cstdint>
#include "../vendor/imgui/imgui.h"

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

struct v2 {
	f32 x, y;
};

struct v2i {
	i32 x = 0, y = 0;

	v2i operator+(const v2i& rhs) const { return v2i{ x + rhs.x, y + rhs.y }; }
	v2i operator-(const v2i& rhs) const { return v2i{ x - rhs.x, y - rhs.y }; }
	v2i operator*(const v2i& rhs) const { return v2i{ x * rhs.x, y * rhs.y }; }
	v2i operator/(const v2i& rhs) const { return v2i{ x / rhs.x, y / rhs.y }; }

	operator bool() const {
		return !(x == 0 && y == 0);
	}
};

struct v3 {
	f32 x, y, z;

	v3() : x(0.f), y(0.f), z(0.f) { }
	v3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) { }

	v3 operator+(const v3& other) {
		return v3{ x + other.x, y + other.y, z + other.z };
	}
};

struct v4 {
	f32 x, y, width, height;
};

struct bbox_t {
	f32 x, y, w, h;
};

class vmatrix_t {
public:
	auto operator[](int i) const noexcept { return m[i]; }

	float m[4][4];
};

struct col_t {
	i32 r, g, b, a;

	col_t() : r(0), g(0), b(0), a(0) { }
	col_t(i32 r, i32 g, i32 b, i32 a = 255) : r(r), g(g), b(b), a(a) { }

	operator ImU32() const {
		return IM_COL32(r, g, b, a);
	}

	static col_t white(i32 alpha = 255) {
		return col_t(255, 255, 255, alpha);
	}

	static col_t black(i32 alpha = 255) {
		return col_t(0, 0, 0, alpha);
	}
};

template <typename T>
class CNetworkUtlVectorBase {
public:
	auto begin() const { return m_data; }
	auto end() const { return m_data + m_size; }

	int m_size;
	char pad0[0x4];  // no idea
	T* m_data;
};