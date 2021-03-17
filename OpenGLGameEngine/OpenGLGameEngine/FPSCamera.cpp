#include "FPSCamera.h"



FPSCamera::FPSCamera(Vector3 position, Vector3 up, float yaw, float pitch) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

FPSCamera::FPSCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = Vector3(posX, posY, posZ);
	WorldUp = Vector3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Mat4 FPSCamera::GetViewMatrix()
{
	return Mat4::lookAt(Position, Position + Front, Up);
}

void FPSCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	

	float velocity = MovementSpeed * deltaTime;

	Vector3 FPSFront = Vector3::Cross(WorldUp, Right);

	FPSFront.y = 0;

	if (direction == FORWARD) {

		Position += FPSFront * velocity;

		headMovement++;

	}

	if (direction == BACKWARD) {

		Position -= FPSFront * velocity;

		headMovement++;

	}

	if (direction == LEFT) {

		Position -= Right * velocity;

	}
	if (direction == RIGHT) {

		Position += Right * velocity;

	}
	if (direction == UP) {

		Position += WorldUp * velocity;

	}
	if (direction == DOWN) {

		Position -= WorldUp * velocity;

	}

	Position.y = headbobRate * sin(headMovement * 0.1) + height;

	

}

void FPSCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void FPSCamera::updateCameraVectors()
{

	Vector3 front;
	front.x = cos(toRadians(Yaw)) * cos(toRadians(Pitch));
	front.y = sin(toRadians(Pitch));
	front.z = sin(toRadians(Yaw)) * cos(toRadians(Pitch));
	Front = front.Normalized();

	Right = Vector3::Normalize(Vector3::Cross(Front, WorldUp));
	Up = Vector3::Normalize(Vector3::Cross(Right, Front));

}

