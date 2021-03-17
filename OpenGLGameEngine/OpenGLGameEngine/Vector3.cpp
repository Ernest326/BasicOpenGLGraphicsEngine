#include "Vector3.h"



Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x)
{
	this->x = x;
	this->y = x;
	this->z = x;
}

Vector3::Vector3(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/////////////////////////////

Vector3::~Vector3()
{
}

////////////////////////////////////////////

Vector3& Vector3::multiply(Vector3 other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

Vector3& Vector3::divide(Vector3 other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

Vector3& Vector3::add(Vector3 other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

Vector3& Vector3::subtract(Vector3 other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

/////////////////////////
 
Vector3 & Vector3::multiply(float other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;

	return *this;
}

Vector3 & Vector3::divide(float other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;

	return *this;
}

Vector3 & Vector3::add(float other)
{
	this->x += other;
	this->y += other;
	this->z += other;

	return *this;
}

Vector3 & Vector3::subtract(float other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;

	return *this;
}

////////////////////////////////////////
////Vector Calculations

Vector3 operator*(Vector3 left, const Vector3& right) {

	return left.multiply(right);

}

Vector3 operator/(Vector3 left, const Vector3& right) {

	return left.divide(right);

}

Vector3 operator+(Vector3 left, const Vector3& right) {

	return left.add(right);

}

Vector3 operator-(Vector3 left, const Vector3& right) {

	return left.subtract(right);

}



///////////////////////
//Float calculations

Vector3 operator*(Vector3 left, const float& right)
{
	return left.multiply(right);
}

Vector3 operator/(Vector3 left, const float& right)
{
	return left.divide(right);
}

Vector3 operator+(Vector3 left, const float& right)
{
	return left.add(right);
}

Vector3 operator-(Vector3 left, const float& right)
{
	return left.subtract(right);
}

///////////////////////////////////
//Vector calculations

Vector3 Vector3::operator*=(const Vector3 & other)
{
	return this->multiply(other);
}

Vector3 Vector3::operator/=(const Vector3 & other)
{
	return this->divide(other);
}

Vector3 Vector3::operator+=(const Vector3 & other)
{
	return this->add(other);
}

Vector3 Vector3::operator-=(const Vector3 & other)
{
	return this->subtract(other);
}

///////////////////////////
////Float calculations////

Vector3 Vector3::operator*=(const float other)
{
	return multiply(other);
}

Vector3 Vector3::operator/=(const float other)
{
	return divide(other);
}

Vector3 Vector3::operator+=(const float other)
{
	return add(other);
}

Vector3 Vector3::operator-=(const float other)
{
	return subtract(other);
}

/////////////

float Vector3::DistanceFrom(const Vector3 other)
{
	float result;

	Vector3 difference = Vector3(this->x, this->y, this->z) - other;

	float distance = sqrt(pow(difference.x, 2.0f) + pow(difference.y, 2.0f) + pow(difference.z, 2.0f));

	return distance;
}

///////////////////////////////////

float Vector3::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

/*Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}*/

Vector3 Vector3::Cross(Vector3 vec, Vector3 vec2)
{
	return Vector3(vec.y * vec2.z - vec.z * vec2.y, vec.z * vec2.x - vec.x * vec2.z, vec.x * vec2.y - vec.y * vec2.x);
}

float Vector3::Dot(const Vector3& other)
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::Dot(Vector3 vec, Vector3 vec2)
{
	return vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z;
}

Vector3 Vector3::Normalized() const
{
	float mag = Magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}

Vector3 Vector3::Normalize(Vector3 vec)
{

	float mag = vec.Magnitude();
	Vector3 result(vec.x / mag, vec.y / mag, vec.z / mag);

	return result;

}

///////////////////////////////////

std::ostream & operator<<(std::ostream & stream, const Vector3 & vector)
{
	return stream << vector.x << " , " << vector.y << " , " << vector.z << std::endl;
}
