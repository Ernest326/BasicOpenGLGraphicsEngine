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

Window window("Skybox example", 1280, 720);

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

	Shader shader("Shaders/3dtexture.vert", "Shaders/3dtexture.frag");
	Shader skyboxshader("Shaders/skybox.vert", "Shaders/skybox.frag");
	Texture2D crateTexture("Textures/container.jpg", GL_REPEAT, GL_LINEAR);
	Texture2D grass("Textures/grass.png", GL_REPEAT, GL_LINEAR);
	Cubemap skybox("Textures/Skyboxes/lake1_bk.jpg", "Textures/Skyboxes/lake1_ft.jpg", "Textures/Skyboxes/lake1_up.jpg", "Textures/Skyboxes/lake1_dn.jpg", "Textures/Skyboxes/lake1_rt.jpg", "Textures/Skyboxes/lake1_lf.jpg", true);

	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};


	VertexArray VAO;

	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 3), 0, 5, 0);
	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 2), 1, 5, 3);

	VertexArray SkyBox;

	SkyBox.addBuffer(new Buffer(skyboxVertices, sizeof(skyboxVertices), 3), 0, 3, 0);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	while (!window.closed()) {

		window.clear();

		calculateDeltaTime();
		processInput();

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, crateTexture.getTexture());

		shader.enable();

		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		//--------------------------------------

		Mat4 model = Mat4::translate(Vector3(0.0f));
		Mat4 view = cam.GetViewMatrix(); //Mat4::lookAt(Vector3(camX, 0.0f, camZ), Vector3(0.0f), Vector3(0.0f, 1.0f, 0.0f));
		Mat4 projection = Mat4::perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		shader.SetMatrix4("model", model);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();
		glBindTexture(GL_TEXTURE_2D, 0);

		//----------------------------------------

		Mat4 model2 = Mat4::translate(Vector3(0.0f, -0.76f, 0.0f));
		model2.scale(Vector3(25.0f, 0.5f, 25.0f));

		shader.SetMatrix4("model", model2);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);

		glBindTexture(GL_TEXTURE_2D, grass.getTexture());

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();

		glBindTexture(GL_TEXTURE_2D, 0);

		shader.disable();

		//------------------------------------

		glDepthFunc(GL_LEQUAL);

		skyboxshader.enable();

		Mat4 skyboxView = view;

		skyboxView.elements[3 + 0 * 4] = 0;
		skyboxView.elements[3 + 1 * 4] = 0;
		skyboxView.elements[3 + 2 * 4] = 0;
		skyboxView.elements[0 + 3 * 4] = 0;
		skyboxView.elements[1 + 3 * 4] = 0;
		skyboxView.elements[2 + 3 * 4] = 0;
		skyboxView.elements[3 + 3 * 4] = 0;

		skyboxshader.SetMatrix4("view", skyboxView);
		skyboxshader.SetMatrix4("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getCubemap());

		SkyBox.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		SkyBox.unbind();

		glDepthFunc(GL_LESS);

		window.update();

	}

	glfwTerminate();
	return 0;

}



//If possible make a class for loading and rendering models

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


