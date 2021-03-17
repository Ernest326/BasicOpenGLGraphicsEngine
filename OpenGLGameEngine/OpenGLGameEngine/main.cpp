#include "Window.h"
#include "Vectors.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Buffers.h"
#include "Camera.h"
#include "FPSCamera.h"
#include "Cubemap.h"
#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Window window("My OpenGL Game Engine", 1280, 720);

Camera cam(Vector3(10.0f, 3.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

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
	Shader modelShader("Shaders/model.vert", "Shaders/model.frag");

	Texture2D crateTexture("Textures/container.jpg", GL_REPEAT, GL_LINEAR);
	Texture2D grass("Textures/grass.png", GL_REPEAT, GL_LINEAR);
	Cubemap skybox("Textures/Skyboxes/lake1_bk.jpg", "Textures/Skyboxes/lake1_ft.jpg", "Textures/Skyboxes/lake1_up.jpg", "Textures/Skyboxes/lake1_dn.jpg", "Textures/Skyboxes/lake1_rt.jpg", "Textures/Skyboxes/lake1_lf.jpg", true);

	//Cube Vertices
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

	//Skybox vertices
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

	//Texture coords
	float texture[] = {

		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f

	};

	//Texture coords for healthbar
	float healthvertices[] = {

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

	};
	

	VertexArray VAO;
	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 3), 0, 5, 0);
	VAO.addBuffer(new Buffer(vertices, sizeof(vertices), 2), 1, 5, 3);

	//Skybox
	VertexArray SkyBox;
	SkyBox.addBuffer(new Buffer(skyboxVertices, sizeof(skyboxVertices), 3), 0, 3, 0);

	//Enable some opengl stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	//Disable mouse so you can look around
	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Add a callback void so whenever you move your mouse you look around
	glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

	//Set the camera movement speed
	cam.MovementSpeed = 10;

	while (!window.closed()) {

		//Clear the window
		window.clear();

		//Caluclate delta time
		calculateDeltaTime();

		//Check for input
		processInput();

		//Set the active texture to 0 for textures
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, crateTexture.getTexture());

		shader.enable();

		//--------------------------------------
		//Crate

		Mat4 crate = Mat4::translate(Vector3(0.0f));
		Mat4 view = cam.GetViewMatrix(); //Mat4::lookAt(Vector3(camX, 0.0f, camZ), Vector3(0.0f), Vector3(0.0f, 1.0f, 0.0f));
		Mat4 projection = Mat4::perspective(60.0f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);

		shader.SetMatrix4("model", crate);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);
		shader.SetFloat("tiling", 1);

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();

		glBindTexture(GL_TEXTURE_2D, 0);

		//_----------------------------------
		//Grass

		glBindTexture(GL_TEXTURE_2D, grass.getTexture());

		Mat4 model2 = Mat4::translate(Vector3(0.0f, -0.76f, 0.0f));
		model2.scale(Vector3(250.0f, 0.5f, 250.0f));

		shader.SetMatrix4("model", model2);
		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);
		shader.SetFloat("tiling", 100);

		VAO.bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		VAO.unbind();

		glBindTexture(GL_TEXTURE_2D, 0);

		shader.disable();

		//--------------------------

		//Skybox

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



//Input

void calculateDeltaTime() {

	deltaTime = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();

}

void processInput() {

	if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {

		cam.ProcessKeyboard(cam.DOWN, deltaTime);
	}
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

}
