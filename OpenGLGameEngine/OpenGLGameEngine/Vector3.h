#pragma once

#include<iostream>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x);
	Vector3(float x, float y);
	Vector3(float x, float y, float z);
	~Vector3();

	Vector3& multiply(Vector3 other);
	Vector3& divide(Vector3 other);
	Vector3& add(Vector3 other);
	Vector3& subtract(Vector3 other);

	Vector3& multiply(float other);
	Vector3& divide(float other);
	Vector3& add(float other);
	Vector3& subtract(float other);

	friend Vector3 operator*(Vector3 left, const Vector3& right);
	friend Vector3 operator/(Vector3 left, const Vector3& right);
	friend Vector3 operator+(Vector3 left, const Vector3& right);
	friend Vector3 operator-(Vector3 left, const Vector3& right);

	Vector3 operator*=(const Vector3& other);
	Vector3 operator/=(const Vector3& other);
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);

	friend Vector3 operator*(Vector3 left, const float& right);
	friend Vector3 operator/(Vector3 left, const float& right);
	friend Vector3 operator+(Vector3 left, const float& right);
	friend Vector3 operator-(Vector3 left, const float& right);

	Vector3 operator*=(const float other);
	Vector3 operator/=(const float other);
	Vector3 operator+=(const float other);
	Vector3 operator-=(const float other);

	float DistanceFrom(const Vector3 other);

	float Magnitude() const;
	//Vector3 Cross(const Vector3& other) const;
	static Vector3 Cross(Vector3 vec, Vector3 vec2);
	float Dot(const Vector3& other);
	static float Dot(Vector3 vec, Vector3 vec2);
	Vector3 Normalized() const;
	static Vector3 Normalize(Vector3 vec);


	friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);

};

