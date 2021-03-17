#pragma once

#include "Vector3.h"

struct Transform
{

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform(Vector3 pos) : position(pos) {};
	Transform(Vector3 pos, Vector3 scl) : position(pos), rotation(scl) {};
	Transform(Vector3 pos, Vector3 scl, Vector3 rot) : position(pos), scale(scl), rotation(rot) {};

	float DistanceFrom(Transform other);
	float DistanceFrom(Vector3 other);

	bool CheckCollision(Transform other);
	bool CheckCollision(Vector3 position, Vector3 scale);

};

