#pragma once

#pragma once

#include"GlobalConsts.h"

#include <sstream>
#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>
#include <limits>

template<typename T>
class Vec3
{
public:
	T x, y, z;

	// Constructors
	Vec3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}

	template<typename U>
	Vec3(U val)
		: x{ static_cast<T>(val) }, y{ static_cast<T>(val) }, z{ static_cast<T>(val) } {
	}

	template<typename U1, typename U2, typename U3>
	Vec3(U1 val1, U2 val2, U3 val3)
		: x{ static_cast<T>(val1) }, y{ static_cast<T>(val2) }, z{ static_cast<T>(val3) } {
	}

	template<typename U1, typename U2>
	Vec3(U1 val1, U2 val2)
		: x{ static_cast<T>(val1) }, y{ static_cast<T>(val2) }, z{ static_cast<T>(0) } {
	}

	template<typename U>
	Vec3(U vals[3])
		: x{ static_cast<T>(vals[0]) }, y{ static_cast<T>(vals[1]) }, z{ static_cast<T>(vals[2]) } {
	}

	template<typename U>
	Vec3(std::array<U, 3> vals)
		: x{ static_cast<T>(vals[0]) }, y{ static_cast<T>(vals[1]) }, z{ static_cast<T>(vals[2]) } {
	}

	Vec3(const Vec3& other)
		: x{ other.x }, y{ other.y }, z{ other.z } {
	}

	// ACCESSORS
	const T& operator [] (uint8_t i) const { return (&x)[i]; }
	T& operator [] (uint8_t i) { return (&x)[i]; }

	static float Dot(const Vec3& a, const Vec3& b)
	{
		return float(a.x * b.x + a.y * b.y + a.z * b.z);
	}

	static Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	}

	static float AngleRad(Vec3& a, Vec3& b)
	{
		float denom = a.Length() * b.Length();
		if (denom == 0.0f)
		{
			std::cerr << "Undefined angle for zero-length vector(s)!\n";
			return 0;
		}
		return std::acos(Dot(a, b) / denom);
	}

	static float AngleDeg(Vec3& a, Vec3& b)
	{
		return (float)RenderConsts::RAD_TO_DEG * AngleRad(a, b);
	}

	static Vec3 Normalize(const Vec3& a)
	{
		float len = a.Length();
		if (len > 0)
		{
			float invLen = 1 / len;
			return Vec3(a.x * invLen, a.y * invLen, a.z * invLen);
		}
		return Vec3(a);
	}

	static float Distance(const Vec3& a, const Vec3& b)
	{
		return std::abs(a.Length() - b.Length());
	}

	static Vec3 Lerp(const Vec3& a, const Vec3& b, float t)
	{
		return a + (b - a) * std::clamp(t, 0.f, 1.f);
	}

	static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, float t)
	{
		return a + (b - a) * t;
	}

	static Vec3 Max(const Vec3& a, const Vec3& b)
	{
		return Vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
	}

	static Vec3 Min(const Vec3& a, const Vec3& b)
	{
		return Vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
	}

	static bool InRange(const Vec3& a, const Vec3& b, float threshold)
	{
		return Distance(a, b) <= threshold;
	}

	// Instance Methods

	bool Equals(const Vec3& a) const
	{
		return (a.x == *this.x) && (a.y == *this.y) && (a.z == *this.z);
	}

	float SqrLength() const
	{
		return x * x + y * y + z * z;
	}

	float Length() const
	{
		return std::sqrt(SqrLength());
	}

	Vec3& Normalize()
	{
		float len = Length();
		if (len > 0)
		{
			float invLen = 1 / len;
			x *= static_cast<T>(invLen);
			y *= static_cast<T>(invLen);
			z *= static_cast<T>(invLen);
		}
		return *this;
	}

	template<typename U1, typename U2, typename U3>
	void Set(U1 newX, U2 newY, U3 newZ)
	{
		x = static_cast<T>(newX);
		y = static_cast<T>(newY);
		z = static_cast<T>(newZ);
	}

	template<typename U>
	void Set(U vals[3])
	{
		x = static_cast<T>(vals[0]);
		y = static_cast<T>(vals[1]);
		z = static_cast<T>(vals[2]);
	}

	void Set(const Vec3& newV)
	{
		x = newV.x;
		y = newV.y;
		z = newV.z;
	}

	std::string Display() const
	{
		std::ostringstream stream{};
		stream << "[ " << x << ", " << y << ", " << z << " ]";
		return stream.str();
	}

	void MoveTowards(const Vec3& target, float maxDistanceDelta)
	{
		Vec3 dir = target - *this;
		float delta = std::clamp(maxDistanceDelta, 0.0f, dir.Length());
		Set(Add(*this, delta * Normalize(dir)));
	}

	// Operator Overloads
	friend Vec3 operator+(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend Vec3 operator-(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend Vec3 operator*(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	friend Vec3 operator*(float t, const Vec3& a)
	{
		return Vec3(t * a.x, t * a.y, t * a.z);
	}

	friend Vec3 operator*(const Vec3& a, float t)
	{
		return t * a;
	}

	friend Vec3 operator/(const Vec3& a, float t)
	{
		return (1.0f / t) * a;
	}

	friend bool operator==(const Vec3& a, const Vec3& b)
	{
		return Equals(a, b);
	}

	friend Vec3 operator-(const Vec3& a)
	{
		return Vec3(-a.x, -a.y, -a.z);
	}

	friend Vec3& operator+=(Vec3& a, const Vec3& b)
	{
		a = a + b;
		return a;
	}

	friend Vec3& operator-=(Vec3& a, const Vec3& b)
	{
		a = a - b;
		return a;
	}

	friend Vec3& operator*=(Vec3& a, float val)
	{
		a = a * val;
		return a;
	}

	friend Vec3& operator*=(Vec3& a, const Vec3& b)
	{
		a = a * b;
		return a;
	}

	friend Vec3& operator/=(Vec3& a, float val)
	{
		a = a / val;
		return a;
	}

	friend Vec3& operator/=(Vec3& a, const Vec3& b)
	{
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		return a;
	}
};
