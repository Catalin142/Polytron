#pragma once

#include <string>
struct GLFWwindow;

class Window
{
public:
	Window(const std::string& title, unsigned int width, unsigned int height);
	~Window();

	void Update();

	void set_vSync(bool set);

	GLFWwindow* GLWindow;

	std::string Title;
	unsigned int Width;
	unsigned int Height;

	bool isRunning = true;

	static Window* Get() { return m_Instance; }

private:
	bool m_vSync = true;
	static Window* m_Instance;
};