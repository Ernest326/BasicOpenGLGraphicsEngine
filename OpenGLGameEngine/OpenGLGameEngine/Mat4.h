#pragma once

#include <iostream>
#include "maths_func.h"
#include <GL/glew.h>
#include "Vector3.h"

struct Mat4 {

	GLfloat elements[4 * 4];

	Mat4();
	Mat4(float value);



	static Mat4 identity() { return Mat4(1.0f); }

	static Mat4 perspective(float fov, float aspectratio, float near, float far);
	static Mat4 orthographic(float top, float bottom, float left, float right, float near, float far);

	static Mat4 lookAt(const Vector3& camera, const Vector3& target, const Vector3& up);

	Mat4 scale(float x, float y, float z);
	Mat4 scale(Vector3 value);
	Mat4 translate(float x, float y, float z);
	static Mat4 translate(Vector3 value);
	static Mat4 rotation(float angle, float xaxis, float yaxis, float zaxis);
	static Mat4 rotation(float angle, Vector3 axis);

	Mat4 multiply(Mat4 other);
	Mat4 divide(Mat4 other);
	Mat4 add(Mat4 other);
	Mat4 subtract(Mat4 other);

	friend Mat4& operator*(Mat4& left, const Mat4& right);
	friend Mat4& operator/(Mat4& left, const Mat4& right);
	friend Mat4& operator+(Mat4& left, const Mat4& right);
	friend Mat4& operator-(Mat4& left, const Mat4& right);

	Mat4& operator*=(const Mat4& other);
	Mat4& operator/=(const Mat4& other);
	Mat4& operator+=(const Mat4& other);
	Mat4& operator-=(const Mat4& other);

	friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);

};