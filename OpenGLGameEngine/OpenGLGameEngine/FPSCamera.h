#include <GL/glew.h>
#include "Mat4.h"
#include "Vector3.h"
#include "Transform.h"

class FPSCamera
{
private:

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 15.0f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 4.0f;

	float headMovement = 0;
	float height = 3.0f;

public:

	FPSCamera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// Default camera value

	Vector3 Position;
	Vector3 Front;
	Vector3 Up;
	Vector3 Right;
	Vector3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float headbobRate = 0.2;
	float MouseSensitivity;
	float Zoom;

	Mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
	void updateCameraVectors();

};