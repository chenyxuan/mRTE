#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <cstdlib>

struct vec3 {
	float e[3];
	
	vec3() {}
	vec3(float e0,float e1,float e2) { e[0] = e0, e[1] = e1, e[2] = e2; }

	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	float r() const { return e[0]; }
	float g() const { return e[1]; }
	float b() const { return e[2]; }

	const vec3& operator+() const { return *this; }
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	float operator[](int i) const { return e[i]; }
	float& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3 &rhs) {
		e[0] += rhs.e[0], e[1] += rhs.e[1], e[2] += rhs.e[2];
		return *this;
	}
	vec3& operator-=(const vec3 &rhs) {
		e[0] -= rhs.e[0], e[1] -= rhs.e[1], e[2] -= rhs.e[2];
		return *this;
	}
	vec3& operator*=(const vec3 &rhs) {
		e[0] *= rhs.e[0], e[1] *= rhs.e[1], e[2] *= rhs.e[2];
		return *this;
	}
	vec3& operator/=(const vec3 &rhs) {
		e[0] /= rhs.e[0], e[1] /= rhs.e[1], e[2] /= rhs.e[2];
		return *this;
	}
	vec3& operator*=(const float t) {
		e[0] *= t, e[1] *= t, e[2] *= t;
		return *this;
	}
	vec3& operator/=(const float t) {
		e[0] /= t, e[1] /= t, e[2] /= t;
		return *this;
	}
	
	vec3 operator+(const vec3 &rhs) const {
		return vec3(e[0] + rhs.e[0], e[1] + rhs.e[1], e[2] + rhs.e[2]);
	}
	vec3 operator-(const vec3 &rhs) const {
		return vec3(e[0] - rhs.e[0], e[1] - rhs.e[1], e[2] - rhs.e[2]);
	}
	vec3 operator*(const vec3 &rhs) const {
		return vec3(e[0] * rhs.e[0], e[1] * rhs.e[1], e[2] * rhs.e[2]);
	}
	vec3 operator/(const vec3 &rhs) const {
		return vec3(e[0] / rhs.e[0], e[1] / rhs.e[1], e[2] / rhs.e[2]);
	}
	vec3 operator*(const float t) const {
		return vec3(e[0] * t, e[1] * t, e[2] * t);
	}
	vec3 operator/(const float t) const {
		return vec3(e[0] / t, e[1] / t, e[2] / t);
	}
	friend vec3 operator*(const float t,const vec3 &rhs) {
		return vec3(t * rhs.e[0], t * rhs.e[1], t * rhs.e[2]);
	}
		
	float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	vec3 unit_vector() const {
		return *this / length();
	}
	void make_unit_vector() {
		*this = unit_vector();
	}
};

float dot(const vec3 &v1, const vec3 &v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
				v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
				v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

#endif
