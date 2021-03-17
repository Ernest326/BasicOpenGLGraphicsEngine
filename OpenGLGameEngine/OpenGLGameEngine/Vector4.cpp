#include "Vector4.h"



Vector4::Vector4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4::Vector4(float x)
{
	this->x = x;
	this->y = x;
	this->z = x;
	this->w = x;
}

Vector4::Vector4(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

/////////////////////////////

Vector4::~Vector4()
{
}

////////////////////////////////////////////

Vector4& Vector4::multiply(Vector4 other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;

	return *this;
}

Vector4& Vector4::divide(Vector4 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;

	return *this;
}

Vector4& Vector4::add(Vector4 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;

	return *this;
}

Vector4& Vector4::subtract(Vector4 other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;

	return *this;
}

////////////////////////////////////////
Vector4& operator*(Vector4& left, Vector4& right) {

	return left.multiply(right);

}

Vector4& operator/(Vector4& left, Vector4& right) {

	return left.divide(right);

}

Vector4& operator+(Vector4& left, Vector4& right) {

	return left.add(right);

}

Vector4& operator-(Vector4& left, Vector4& right) {

	return left.subtract(right);

}

///////////////////////////////////

Vector4 Vector4::operator*=(const Vector4 & other)
{
	return this->multiply(other);
}

Vector4 Vector4::operator/=(const Vector4 & other)
{
	return this->divide(other);
}

Vector4 Vector4::operator+=(const Vector4 & other)
{
	return this->add(other);
}

Vector4 Vector4::operator-=(const Vector4 & other)
{
	return this->subtract(other);
}

///////////////////////////////////

std::ostream & operator<<(std::ostream & stream, const Vector4 & vector)
{
	return stream << vector.x << " , " << vector.y << " , " << vector.z << " , " << vector.w << std::endl;
}
