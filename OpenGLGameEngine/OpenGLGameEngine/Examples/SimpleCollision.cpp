/*#include "Window.h"
#include "Vectors.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Buffers.h"
#include "Camera.h"
#include "Cubemap.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Window window("Simple Collision Example", 1280, 720);

Camera cam(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

float lastX;
float lastY;
bool firstMouse = true;

float deltaTime;
float lastFrame;

void calculateDeltaTime();
void processInput();

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main() {

	Shader shader("Shaders/pointlight.vert", "Shaders/pointlight.frag");


	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	float vertices2[] =
	{
		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	 1.0f,  1.0f, 1.0f
	};


	VertexArray VAO;

	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 3), 0, 6, 0);
	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 3), 1, 6, 3);

	VertexArray VAO2;

	VAO2.addBuffer(new Buffer(vertices2, sizeof(vertices2), 3), 0, 6, 0);
	VAO2.addBuffer(new Buffer(vertices2, sizeof(vertices2), 3), 1, 6, 3);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	float cubeYPos = 0.0;

	while (!window.closed()) {

		window.clear();

		calculateDeltaTime();
		processInput();

		shader.enable();

		Vector3 lightPos(0.0, 2.0, 0.0);

		//--------------------------------------

		Vector3 cubePos(0.0, cubeYPos, 0.0);
		Vector3 cubeScale(1.0, 1.0, 1.0);
		Vector3 platformPos(0.0, -5.0, 0.0);
		Vector3 platformScale(10.0, 1.0, 10.0);

		bool collisionX = cubePos.x + cubeScale.x >= platformPos.x &&
			platformPos.x + platformScale.x >= cubePos.x;

		bool collisionY = cubePos.y + cubeScale.y >= platformPos.y &&
			platformPos.y + platformScale.y >= cubePos.y;

		bool collisionZ = cubePos.z + cubeScale.z >= platformPos.z &&
			platformPos.z + platformScale.z >= cubePos.z;

		bool collision = collisionX && collisionY && collisionZ;

		if (collision) {



		}
		else {

			cubeYPos -= 1.0 * deltaTime;

		}



		Mat4 model = Mat4::translate(cubePos);
		model.scale(cubeScale);
		Mat4 view = cam.GetViewMatrix(); //Mat4::lookAt(Vector3(camX, 0.0f, camZ), Vector3(0.0f), Vector3(0.0f, 1.0f, 0.0f));
		Mat4 projection = Mat4::perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		shader.SetMatrix4("model", model);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);

		shader.SetVector3f("ligh.diffuse", Vector3(1.0, 1.0, 1.0));
		shader.SetVector3f("light.specular", Vector3(0.5, 0.5, 0.5));
		shader.SetVector3f("light.ambient", Vector3(0.2, 0.2, 0.2));
		shader.SetVector3f("viewPos", cam.Position);

		shader.SetFloat("light.constant", 1.0f);
		shader.SetFloat("light.linear", 0.09);
		shader.SetFloat("light.quadratic", 0.032);
		shader.SetVector3f("light.position", lightPos);

		shader.SetFloat("light.brightness", 2);

		shader.SetFloat("material.shininess", 8);
		shader.SetVector3f("material.color", Vector3(1.0, 1.0, 1.0));

		shader.SetVector3f("color", Vector3(0.8, 0.8, 0.8));

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();

		shader.disable();

		shader.enable();

		Mat4 model2 = Mat4::translate(platformPos);
		model2.scale(platformScale);

		shader.SetMatrix4("model", model2);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);

		shader.SetVector3f("ligh.diffuse", Vector3(1.0, 1.0, 1.0));
		shader.SetVector3f("light.specular", Vector3(0.5, 0.5, 0.5));
		shader.SetVector3f("light.ambient", Vector3(0.2, 0.2, 0.2));
		shader.SetVector3f("viewPos", cam.Position);

		shader.SetFloat("light.constant", 1.0f);
		shader.SetFloat("light.linear", 0.09);
		shader.SetFloat("light.quadratic", 0.032);
		shader.SetVector3f("light.position", lightPos);

		shader.SetFloat("light.brightness", 2);

		shader.SetFloat("material.shininess", 2);
		shader.SetVector3f("material.color", Vector3(1.0, 1.0, 1.0));

		shader.SetVector3f("color", Vector3(0.8, 0.8, 0.8));

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();

		window.update();

	}

	glfwTerminate();
	return 0;

}

//Camera stuff

void calculateDeltaTime() {

	deltaTime = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();

}

void processInput() {

	if (window.isKeyPressed(GLFW_KEY_W)) {
		cam.ProcessKeyboard(cam.FORWARD, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_A)) {
		cam.ProcessKeyboard(cam.LEFT, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_S)) {
		cam.ProcessKeyboard(cam.BACKWARD, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_D)) {
		cam.ProcessKeyboard(cam.RIGHT, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_SPACE)) {
		cam.ProcessKeyboard(cam.UP, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		cam.ProcessKeyboard(cam.DOWN, deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_Q)) {

		glfwSetWindowShouldClose(window.getWindow(), true);

	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {

		firstMouse = false;
		lastX = xpos;
		lastY = ypos;

	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(xoffset, yoffset, true);

}*/
