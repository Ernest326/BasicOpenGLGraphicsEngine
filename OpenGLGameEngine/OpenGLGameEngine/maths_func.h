#pragma once

#define _USE_MATH_DEFINES
#include <math.h>



inline float toRadians(float degrees) {

	float radian = (float)M_PI / 180.0f;
	float result = degrees * radian;

	return result;

}

inline float dot(float x, float y) {
	return x * y;
}