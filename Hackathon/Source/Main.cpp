#include <memory>
 
#include "imgui.h"
#include "GL/glew.h"
#include "System/Window.h"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Renderer.h"
#include "CircleScene/Circle.h"
#include "GUI/GUI.h"

enum class State
{
	Intro,
	App,
};

static float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

int main()
{
	const std::shared_ptr<Window> window = std::make_shared<Window>("Polytron", 1600, 900);
	const std::shared_ptr<Circle> circle = std::make_shared<Circle>();

	Renderer::Init();
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GUI::onAttach(window);

	std::shared_ptr<Texture> Splash = std::make_shared<Texture>("Resources/Textures/SplashScreen.png");
	std::shared_ptr<Texture> SlideInst = std::make_shared<Texture>("Resources/Textures/SlideInst.png");
	float startAlpha = 1.0f;
	float endAlpha = 0.0f;
	
	State currentState = State::Intro;

	float deltaTime = 0.0f;
	float begTime = 0.0f;
	float lastTime = 0.0f;

	float fadeTime = 2.5f;
	while (window->isRunning)
	{
		begTime = glfwGetTime();
		deltaTime = begTime - lastTime;
		lastTime = begTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Renderer::beginScene(glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f));

		switch (currentState)
		{
		case State::Intro:
			fadeTime -= deltaTime;
			Renderer::drawQuad(Splash->TextureID, { 800.0f, 450.0f }, { 1600.0f, 900.0f }, { 1.0f, 1.0f, 1.0f, lerp(endAlpha, startAlpha, fadeTime) });
			if (fadeTime <= 0.0f)
				currentState = State::App;

			break;

		case State::App:
			GUI::Begin();
			circle->Update(deltaTime);
			GUI::End(window);

			if (circle->m_CurrentTab == CurrentTab::Theory)
				Renderer::drawQuad(SlideInst->TextureID, glm::vec2(490.0f, 25.0f), { 450.0f, 70.0f });

			break;
		}

		window->Update();
		if (glfwGetKey(window->GLWindow, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
			glfwSetWindowShouldClose(window->GLWindow, true);
	}

	GUI::onDetach();
}

/*
TODO:
Tangenta
Numele echipei (spargem_capete)


*/