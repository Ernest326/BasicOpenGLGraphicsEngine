#include "Transform.h"

float Transform::DistanceFrom(Transform other)
{
	float result;

	result = position.DistanceFrom(other.position);

	return result;
}

float Transform::DistanceFrom(Vector3 other)
{
	float result;

	result = position.DistanceFrom(other);

	return result;
}

bool Transform::CheckCollision(Transform other)
{
	bool result;

	bool collisionX = this->position.x + this->scale.x >= other.position.x &&
		other.position.x + other.scale.x >= this->position.x;

	bool collisionY = this->position.y + this->scale.y >= other.position.y &&
		other.position.y + other.scale.y >= this->position.y;

	bool collisionZ = this->position.z + this->scale.z >= other.position.z &&
		other.position.z + other.scale.z >= this->position.z;

	result = collisionX && collisionY && collisionZ;

	return result;
}

bool Transform::CheckCollision(Vector3 position, Vector3 scale)
{
	bool result;

	bool collisionX = this->position.x + this->scale.x >= position.x &&
		position.x + scale.x >= this->position.x;

	bool collisionY = this->position.y + this->scale.y >= position.y &&
		position.y + scale.y >= this->position.y;

	bool collisionZ = this->position.z + this->scale.z >= position.z &&
		position.z + scale.z >= this->position.z;

	result = collisionX && collisionY && collisionZ;

	return result;
}
