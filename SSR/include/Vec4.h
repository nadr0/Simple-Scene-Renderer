#ifndef VEC4_H_
#define VEC4_H_
#include <cmath>

class Vec4
{
public:
	Vec4() {
		e[0] = e[1] = e[2] = e[3] = 0.0;
	}

	Vec4(const Vec4 & v){
			e[0] = v.x();
			e[1] = v.y();
			e[2] = v.z();
			e[3] = v.w();
	}

	explicit Vec4(double e0, double e1, double e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
		e[3] = 0.0;
	}

	Vec4(double e0) {
		e[0] = e0;
		e[1] = e0;
		e[2] = e0;
		e[3] = 0.0;
	}


	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }
	inline double w() const { return e[3]; }

	inline const Vec4& operator+() const { return *this; }
	inline Vec4 operator-() const { return Vec4(-e[0], -e[1], -e[2]); }
	inline double operator[](int i) const { return e[i]; }
	inline double& operator[](int i) { return e[i]; }

	inline Vec4& operator+=(const Vec4 &rhs) {
		e[0] += rhs.e[0];
		e[1] += rhs.e[1];
		e[2] += rhs.e[2];
		return *this;
	}

	inline Vec4& operator-=(const Vec4 &rhs) {
		e[0] -= rhs.e[0];
		e[1] -= rhs.e[1];
		e[2] -= rhs.e[2];
		return *this;
	}

	inline Vec4& operator*=(const Vec4 &rhs) {
		e[0] *= rhs.e[0];
		e[1] *= rhs.e[1];
		e[2] *= rhs.e[2];
		return *this;
	}

	inline Vec4& operator/=(const Vec4 &rhs) {
		e[0] /= rhs.e[0];
		e[1] /= rhs.e[1];
		e[2] /= rhs.e[2];
		return *this;
	}

	inline Vec4& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline Vec4& operator/=(const double t) {
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	}

	inline double length() const {
		return std::sqrt(squaredLength());
	}
	inline double squaredLength() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	double e[4];
};

inline Vec4 operator+(Vec4 lhs, const Vec4& rhs) {
	lhs += rhs;
	return lhs;
}

inline Vec4 operator-(Vec4 lhs, const Vec4& rhs) {
	lhs -= rhs;
	return lhs;
}

inline Vec4 operator*(Vec4 lhs, const Vec4& rhs) {
	lhs *= rhs;
	return lhs;
}

inline Vec4 operator*(Vec4 lhs, const double& rhs) {
	lhs *= rhs;
	return lhs;
}

inline Vec4 operator/(Vec4 lhs, const Vec4& rhs) {
	lhs /= rhs;
	return lhs;
}

inline Vec4 operator/(Vec4 lhs, const double rhs) {
	lhs /= rhs;
	return lhs;
}

inline Vec4 normalize(Vec4 v) {
	return v / v.length();
}

inline double dot(const Vec4& v1, const Vec4& v2) {
	return v1.e[0] * v2.e[0] +
		v1.e[1] * v2.e[1] +
		v1.e[2] * v2.e[2];
}

inline Vec4 cross(const Vec4& v1, const Vec4& v2) {
	return Vec4((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}
#endif
