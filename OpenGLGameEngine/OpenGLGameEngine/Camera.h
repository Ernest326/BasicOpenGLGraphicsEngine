#include <GL/glew.h>
#include "Mat4.h"
#include "Vector3.h"

class Camera
{
private:

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 15.0f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 4.0f;

public:

	Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

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
	float MouseSensitivity;
	float Zoom;


	Mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);


private:
	void updateCameraVectors();

};