#include <iostream>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
Window* Window::m_Instance;

void GLAPIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
	const GLchar* message, const void* data)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:   std::cout << message << std::endl; DebugBreak(); return;
	case GL_DEBUG_SEVERITY_MEDIUM: std::cout << message << std::endl; DebugBreak(); return;
	default:																	    return;
	}
}

Window::Window(const std::string& title, unsigned int width, unsigned int height) : Title(title), Width(width), Height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLWindow = glfwCreateWindow(Width, Height, Title.c_str(), NULL/*glfwGetPrimaryMonitor()*/, NULL);
	glfwMakeContextCurrent(GLWindow);

	glewInit();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_TRUE);

	glfwSwapInterval(m_vSync);

	glViewport(0, 0, Width, Height);

	glfwSetFramebufferSizeCallback(GLWindow, [](GLFWwindow* window, int Width, int Height) -> void
		{
			glViewport(0, 0, Width, Height);
		});

	glfwSetWindowSizeCallback(GLWindow, [](GLFWwindow* window, int Width, int Height) -> void
		{
			glViewport(0, 0, Width, Height);
		});

	m_Instance = this;
}

Window::~Window()
{
	glfwDestroyWindow(GLWindow);
	glfwTerminate();
}

void Window::Update()
{
	isRunning = !glfwWindowShouldClose(GLWindow);
	glfwSwapBuffers(GLWindow);
	glfwPollEvents();
}

void Window::set_vSync(bool set)
{
	m_vSync = set;
	glfwSwapInterval(m_vSync);
}
