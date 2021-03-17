#include "Vector2.h"



Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x)
{
	this->x = x;
	this->y = x;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

/////////////////////////////

Vector2::~Vector2()
{
}

////////////////////////////////////////////

Vector2& Vector2::multiply(Vector2 other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

Vector2& Vector2::divide(Vector2 other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

Vector2& Vector2::add(Vector2 other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector2& Vector2::subtract(Vector2 other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

////////////////////////////////////////
Vector2& operator*(Vector2& left, Vector2& right) {

	return left.multiply(right);

}

Vector2& operator/(Vector2& left, Vector2& right) {

	return left.divide(right);

}

Vector2& operator+(Vector2& left, Vector2& right) {

	return left.add(right);

}

Vector2& operator-(Vector2& left, Vector2& right) {

	return left.subtract(right);

}

///////////////////////////////////

Vector2 Vector2::operator*=(const Vector2 & other)
{
	return this->multiply(other);
}

Vector2 Vector2::operator/=(const Vector2 & other)
{
	return this->divide(other);
}

Vector2 Vector2::operator+=(const Vector2 & other)
{
	return this->add(other);
}

Vector2 Vector2::operator-=(const Vector2 & other)
{
	return this->subtract(other);
}

///////////////////////////////////

std::ostream & operator<<(std::ostream & stream, const Vector2 & vector)
{
	return stream << vector.x << " , " << vector.y << std::endl;
}
