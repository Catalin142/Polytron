#pragma once

#include "GLFW/glfw3.h"
#include "Window.h"
#include "glm/glm.hpp"

static glm::vec2 getMosuePosition()
{
	double x, y;
	glfwGetCursorPos(Window::Get()->GLWindow, &x, &y);
	y = 900 - y;
	return { x, y };
}

static float getMouseX()
{
	return getMosuePosition().x;
}

static float getMouseY()
{
	return getMosuePosition().y;
}

static bool isKeyPressed(unsigned int key)
{
	if (glfwGetKey(Window::Get()->GLWindow, key) == GLFW_PRESS)
		return true;
	return false;
}

static bool isKeyReleased(unsigned int key)
{
	if (glfwGetKey(Window::Get()->GLWindow, key) == GLFW_RELEASE)
		return true;
	return false;
}