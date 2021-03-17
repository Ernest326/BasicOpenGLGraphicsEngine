#include "Mat4.h"

Mat4::Mat4()
{
	
	for (int i = 0; i < 4 * 4; i++) {

		elements[i] = 0.0f;

	}

}

Mat4::Mat4(float value)
{

	for (int i = 0; i < 4 * 4; i++) {

		elements[i] = 0.0f;

	}

	for (int i = 0; i < 4; i++) {

		elements[i + i * 4] = value;

	}


}

Mat4 Mat4::perspective(float fov, float aspectratio, float near, float far)
{

	Mat4 result;

	float angle = 1.0f / tan(toRadians(0.5f * fov));

	result.elements[0 + 0 * 4] = angle / aspectratio;
	result.elements[1 + 1 * 4] = angle;
	result.elements[2 + 2 * 4] = (near + far) / (near - far);
	result.elements[3 + 2 * 4] = -1.0f;
	result.elements[2 + 3 * 4] = (2.0f * near * far) / (near - far);

	return result;
}

Mat4 Mat4::orthographic(float top, float bottom, float left, float right, float near, float far)
{

	Mat4 result;

	result.elements[0 + 0 * 4] = (2) / (right - left);;
	result.elements[3 + 0 * 4] = -(right + left) / (right - left);
	result.elements[1 + 1 * 4] = (2) / (top - bottom);
	result.elements[3 + 1 * 4] = -(top + bottom) / (top - bottom);
	result.elements[2 + 2 * 4] = (2) / (far - near);;
	result.elements[3 + 2 * 4] = -(far + near) / (far - near);
	result.elements[3 + 3 * 4] = 1;

	return result;
}

Mat4 Mat4::lookAt(const Vector3& camera, const Vector3& target, const Vector3& up)
{
	Mat4 result = identity();
	Vector3 f = Vector3::Normalize(target - camera);
	Vector3 s = Vector3::Normalize(Vector3::Cross(f, up));
	Vector3 u = Vector3::Cross(s, f);

	result.elements[0 + 0 * 4] = s.x;
	result.elements[0 + 1 * 4] = s.y;
	result.elements[0 + 2 * 4] = s.z;

	result.elements[1 + 0 * 4] = u.x;
	result.elements[1 + 1 * 4] = u.y;
	result.elements[1 + 2 * 4] = u.z;

	result.elements[2 + 0 * 4] = -f.x;
	result.elements[2 + 1 * 4] = -f.y;
	result.elements[2 + 2 * 4] = -f.z;

	result.elements[0 + 3 * 4] = -Vector3::Dot(s, camera);
	result.elements[1 + 3 * 4] = -Vector3::Dot(u, camera);
	result.elements[2 + 3 * 4] = Vector3::Dot(f, camera);

	return result;
}

Mat4 Mat4::scale(float x, float y, float z)
{
	elements[0 + 0 * 4] *= x;
	elements[1 + 1 * 4] *= y;
	elements[2 + 2 * 4] *= z;

	return *this;
}

Mat4 Mat4::scale(Vector3 value)
{
	elements[0 + 0 * 4] *= value.x;
	elements[1 + 1 * 4] *= value.y;
	elements[2 + 2 * 4] *= value.z;

	return *this;
}

Mat4 Mat4::translate(float x, float y, float z)
{
	elements[3] = x;
	elements[7] = y;
	elements[11] = z;

	return *this;
}

Mat4 Mat4::translate(Vector3 value)
{
	Mat4 result(1.0f);

	result.elements[12] = value.x;
	result.elements[13] = value.y;
	result.elements[14] = value.z;

	return result;
}

Mat4 Mat4::rotation(float angle, float xaxis, float yaxis, float zaxis)
{
	Mat4 result(1.0f);

	float r = toRadians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	Vector3 axis(xaxis, yaxis, zaxis);
	Vector3 normaxis = axis.Normalized();

	float x = normaxis.x;
	float y = normaxis.y;
	float z = normaxis.z;

	result.elements[0 + 0 * 4] = x * x * omc + c;
	result.elements[0 + 1 * 4] = x * y * omc - z * s;
	result.elements[0 + 2 * 4] = x * z * omc + y * s;

	result.elements[1 + 0 * 4] = x * y * omc + z * s;
	result.elements[1 + 1 * 4] = y * y * omc + c;
	result.elements[1 + 2 * 4] = y * z * omc - x * s;

	result.elements[2 + 0 * 4] = x * z * omc - y * s;
	result.elements[2 + 1 * 4] = y * z * omc + x * s;
	result.elements[2 + 2 * 4] = z * z * omc + c;

	return result;
}

Mat4 Mat4::rotation(float angle, Vector3 axis)
{
	Mat4 result(1.0f);

	float r = toRadians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	Vector3 normaxis = axis.Normalized();
		
	float x = normaxis.x;
	float y = normaxis.y;
	float z = normaxis.z;

	result.elements[0 + 0 * 4] = x * x * omc + c;
	result.elements[0 + 1 * 4] = x * y * omc - z * s;
	result.elements[0 + 2 * 4] = x * z * omc + y * s;
								 	   
	result.elements[1 + 0 * 4] = x * y * omc + z * s;
	result.elements[1 + 1 * 4] = y * y * omc + c;
	result.elements[1 + 2 * 4] = y * z * omc - x * s;
								 	   
	result.elements[2 + 0 * 4] = x * z * omc - y * s;
	result.elements[2 + 1 * 4] = y * z * omc + x * s;
	result.elements[2 + 2 * 4] = z * z * omc + c;

	return result;

}

Mat4 Mat4::multiply(Mat4 other)
{

	for (int x = 0; x < 4; x++) {

		for (int y = 0; y < 4; y++) {

			elements[x + y * 4] *= other.elements[x + y * 4];

		}

	}

	return *this;

}

Mat4 Mat4::divide(Mat4 other)
{

	for (int x = 0; x < 4; x++) {

		for (int y = 0; y < 4; y++) {

			elements[x + y * 4] /= other.elements[x + y * 4];

		}

	}

	return *this;

}

Mat4 Mat4::add(Mat4 other)
{
	for (int x = 0; x < 4; x++) {

		for (int y = 0; y < 4; y++) {

			elements[x + y * 4] += other.elements[x + y * 4];

		}

	}

	return *this;
}

Mat4 Mat4::subtract(Mat4 other)
{
	for (int x = 0; x < 4; x++) {

		for (int y = 0; y < 4; y++) {

			elements[x + y * 4] -= other.elements[x + y * 4];

		}

	}

	return *this;
}

Mat4 & Mat4::operator*=(const Mat4 & other)
{
	return multiply(other);
}

Mat4 & Mat4::operator/=(const Mat4 & other)
{
	return divide(other);
}

Mat4 & Mat4::operator+=(const Mat4 & other)
{
	return add(other);
}

Mat4 & Mat4::operator-=(const Mat4 & other)
{
	return subtract(other);
}

Mat4 & operator*(Mat4 & left, const Mat4 & right)
{
	return left.multiply(right);
}

Mat4 & operator/(Mat4 & left, const Mat4 & right)
{
	return left.divide(right);
}

Mat4 & operator+(Mat4 & left, const Mat4 & right)
{
	return left.add(right);
}

Mat4 & operator-(Mat4 & left, const Mat4 & right)
{
	return left.subtract(right);
}

std::ostream& operator<<(std::ostream& stream, const Mat4& matrix) {

	stream << matrix.elements[0] << " " << matrix.elements[1] << " " << matrix.elements[2] << " " << matrix.elements[3] << "\n" <<
		matrix.elements[4] << " " << matrix.elements[5] << " " << matrix.elements[6] << " " << matrix.elements[7] << "\n" <<
		matrix.elements[8] << " " << matrix.elements[9] << " " << matrix.elements[10] << " " << matrix.elements[11] << "\n" <<
		matrix.elements[12] << " " << matrix.elements[13] << " " << matrix.elements[14] << " " << matrix.elements[15] << std::endl;

	return stream;

}