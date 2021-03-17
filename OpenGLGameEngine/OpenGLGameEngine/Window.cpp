#include "Window.h"

void window_size_callback(GLFWwindow* window, int x, int y);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Window::~Window()
{
}

Window::Window(char* title, int width, int height)
{

	this->m_title = title;
	this->m_width = width;
	this->m_height = height;

	if (!init()) {

		std::cout << "ERROR: Failed the process of initializing window!" << std::endl;

	}

}

bool Window::init()
{

	if (!glfwInit()) {
		std::cout << "ERROR: Failed to initialize GLFW!" << std::endl;
		return false;
	}

	m_window = glfwCreateWindow(m_width, m_height, m_title, GL_FALSE, GL_FALSE);

	if (!m_window) {
		std::cout << "ERROR: Failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);

	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR: Failed to initialize GLEW!" << std::endl;
		return false;
	}

	for (int i = 0; i < MAX_KEYS; i++) {
		m_key[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++) {
		m_button[i] = false;
	}

	return true;

}

void Window::clear() const
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void Window::update() const
{

	glfwSwapBuffers(m_window);
	glfwPollEvents();

}

bool Window::isKeyPressed(unsigned int key) const
{
	if (key >= MAX_KEYS) {
		return false;
	}

	return m_key[key];
}

bool Window::isButtonPressed(unsigned int button) const
{
	if (button >= MAX_BUTTONS) {
		return false;
	}

	return m_button[button];
}

void window_size_callback(GLFWwindow* window, int x, int y) {

	glViewport(0, 0, x, y);

	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->m_width = x;
	win->m_height = y;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->m_key[key] = action != GLFW_RELEASE;

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {

	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->m_button[button] = action != GLFW_RELEASE;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->mousex = xpos;
	win->mousey = ypos;

	if (win->firstMouse) {

		win->firstMouse = false;

		win->lastx = xpos;
		win->lasty = ypos;

	}

	float xoffset = xpos - win->lastx;
	float yoffset = win->lasty - ypos;

	win->lastx = xpos;
	win->lasty = ypos;

	
}