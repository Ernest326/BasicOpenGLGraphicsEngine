#pragma once

#include<iostream>

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float x);
	Vector2(float x, float y);
	~Vector2();

	Vector2& multiply(Vector2 other);
	Vector2& divide(Vector2 other);
	Vector2& add(Vector2 other);
	Vector2& subtract(Vector2 other);

	friend Vector2& operator*(Vector2& left, Vector2& right);
	friend Vector2& operator/(Vector2& left, Vector2& right);
	friend Vector2& operator+(Vector2& left, Vector2& right);
	friend Vector2& operator-(Vector2& left, Vector2& right);

	Vector2 operator*=(const Vector2& other);
	Vector2 operator/=(const Vector2& other);
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);

};

