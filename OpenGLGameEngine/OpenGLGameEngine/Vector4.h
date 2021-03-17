#pragma once

#include<iostream>

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float x);
	Vector4(float x, float y);
	Vector4(float x, float y, float z);
	Vector4(float x, float y, float z, float w);
	~Vector4();

	Vector4& multiply(Vector4 other);
	Vector4& divide(Vector4 other);
	Vector4& add(Vector4 other);
	Vector4& subtract(Vector4 other);

	friend Vector4& operator*(Vector4& left, Vector4& right);
	friend Vector4& operator/(Vector4& left, Vector4& right);
	friend Vector4& operator+(Vector4& left, Vector4& right);
	friend Vector4& operator-(Vector4& left, Vector4& right);

	Vector4 operator*=(const Vector4& other);
	Vector4 operator/=(const Vector4& other);
	Vector4 operator+=(const Vector4& other);
	Vector4 operator-=(const Vector4& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);

};

