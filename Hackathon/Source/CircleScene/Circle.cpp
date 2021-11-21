#include "Circle.h"
#include "GL/glew.h"
#include "GUI/GUI.h"

#include <sstream>
#include <iostream>

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

static
std::string stringPrecision(float value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << value;
	return out.str();
}

Circle::Circle()
{
	m_Layers[CircleLayer::Radians4] = std::make_shared<Texture>("Resources/Textures/Radians4.png");
	m_Layers[CircleLayer::Degrees4] = std::make_shared<Texture>("Resources/Textures/Degrees4.png");

	m_Layers[CircleLayer::Radians12] = std::make_shared<Texture>("Resources/Textures/Radians12.png");
	m_Layers[CircleLayer::Degrees12] = std::make_shared<Texture>("Resources/Textures/Degrees12.png");

	m_Text.push_back(std::make_shared<Texture>("Resources/Textures/text1.png"));
	m_Text.push_back(std::make_shared<Texture>("Resources/Textures/text2.png"));
	m_Text.push_back(std::make_shared<Texture>("Resources/Textures/text3.png"));
}

void Circle::Update(float deltaTime)
{
	Renderer::drawCircle(m_CirclePosition, m_CircleRadius, 0.025f);
	Renderer::drawLine({ 1000.0f, 900.0f }, { 1000.0f, 200.0f }, 3.0f);
	Renderer::drawLine({ 0.0f, 200.0f }, { 1600.0f, 200.0f }, 3.0f);

	float lineLength = m_CircleRadius + 25.0f;
	Renderer::drawLine(m_CirclePosition, 
		{std::cos(glm::radians(0.0f)) * lineLength + m_CirclePosition.x, std::sin(glm::radians(0.0f)) * lineLength + m_CirclePosition.y }, 3.0f);
	Renderer::drawLine(m_CirclePosition, 
		{ std::cos(glm::radians(90.0f)) * lineLength + m_CirclePosition.x, std::sin(glm::radians(90.0f)) * lineLength + m_CirclePosition.y }, 3.0f);
	Renderer::drawLine(m_CirclePosition, 
		{ std::cos(glm::radians(180.0f)) * lineLength + m_CirclePosition.x, std::sin(glm::radians(180.0f)) * lineLength + m_CirclePosition.y }, 3.0f);
	Renderer::drawLine(m_CirclePosition, 
		{ std::cos(glm::radians(270.0f)) * lineLength + m_CirclePosition.x, std::sin(glm::radians(270.0f)) * lineLength + m_CirclePosition.y }, 3.0f);

	glm::vec2 mouse = getMosuePosition();
	float angle = std::atan2(mouse.x - m_CirclePosition.x, mouse.y - m_CirclePosition.y);
	float A = angle;
	angle -= glm::radians(90.0f);
	Renderer::drawLine(m_CirclePosition, { std::cos(angle) * 249.0f + m_CirclePosition.x, std::sin(-angle) * 249.0f + m_CirclePosition.y }, 4.0f,
		glm::vec4{ 102.0f / 255.0f, 202.0f / 255.0f, 212.0f / 255.0f, 1.0f });

	Renderer::drawLine(m_CirclePosition, { m_CirclePosition.x, std::sin(-angle) * 249.0f + m_CirclePosition.y }, 4.0f,
		glm::vec4{ 73.0f / 255.0f, 49.0f / 255.0f, 145.0f / 255.0f, 1.0f });

	Renderer::drawLine(m_CirclePosition, { std::cos(angle) * 249.0f + m_CirclePosition.x, m_CirclePosition.y }, 4.0f,
		glm::vec4{ 196.0f / 255.0f, 133.0f / 255.0f, 55.0f / 255.0f , 1.0f});

	std::string CurrentItemLayer;

	switch (m_CurrentLayer)
	{
	case CircleLayer::Degrees:
		Renderer::drawQuad(m_Layers[CircleLayer::Degrees4]->TextureID, m_CirclePosition, glm::vec2(m_CircleRadius * 2.8f));
		Renderer::drawQuad(m_Layers[CircleLayer::Degrees12]->TextureID, m_CirclePosition, glm::vec2(m_CircleRadius * 2.8f));
		CurrentItemLayer = "Grade";

		break;

	case CircleLayer::Radians:
		Renderer::drawQuad(m_Layers[CircleLayer::Radians4]->TextureID, m_CirclePosition, glm::vec2(m_CircleRadius * 2.8f));
		Renderer::drawQuad(m_Layers[CircleLayer::Radians12]->TextureID, m_CirclePosition, glm::vec2(m_CircleRadius * 2.8f));
		CurrentItemLayer = "Radiani";

		break;
	}

	float degree = -angle;
	if (degree < 0.0f)
		degree = glm::radians(360.0f) - angle;

	std::string CurrentItemTab;
	switch (m_CurrentTab)
	{
	case CurrentTab::Theory:
		if (isKeyPressed(GLFW_KEY_RIGHT))
		{
			if (m_LastChange > m_ChangeCooldown)
			{
				m_CurrentSlide++;
				m_CurrentSlide %= m_Text.size();
				m_LastChange = 0.0f;
			}
		}
		if (isKeyPressed(GLFW_KEY_LEFT))
		{
			if (m_LastChange > m_ChangeCooldown)
			{
				m_CurrentSlide--;
				if (m_CurrentSlide < 0)
					m_CurrentSlide = m_Text.size() - 1;
				m_LastChange = 0.0f;
			}
		}
		m_LastChange += deltaTime;

		if (isKeyReleased(GLFW_KEY_RIGHT) && isKeyReleased(GLFW_KEY_LEFT))
			m_LastChange = m_ChangeCooldown;

		CurrentItemTab = "Teorie";
		Renderer::drawQuad(m_Text[m_CurrentSlide]->TextureID, { 1300.0f, 530.0f }, { 500.0f, 600.0f });

		break;

	case CurrentTab::Application:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		auto tex = Renderer::drawCube({ 0.0f, 0.0f, -4.9f }, { 1.4f, 1.4f, 1.4f }, angle, m_CubeRotationAxis, { 1.0f, 1.0f, 1.0f, 1.0f });
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		CurrentItemTab = "Aplicarea teoriei";
		Renderer::drawQuad(tex, { 1300.0f, 525.0f }, { 550.0f, 550.0f });

		ImGui::SetNextWindowSize({ 610.0f, 198.0f });
		ImGui::SetNextWindowPos({ 990.0f, 900.0f - 198.0f });
		ImGui::Begin("ApplicationTab", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		bool _X = (int)m_CubeRotationAxis[0], _Y = (int)m_CubeRotationAxis[1], _Z = (int)m_CubeRotationAxis[2];

		auto curPos = ImGui::GetCursorPos();
		curPos.y += 10.0f;

		curPos.x += 210.0f;
		ImGui::SetCursorPos(curPos);
		ImGui_SameLine(ImGui::Text("x:"), ImGui::Checkbox("##x: ", &_X), 10.0f);

		curPos.x += 70.0f;
		ImGui::SetCursorPos(curPos);
		ImGui_SameLine(ImGui::Text("y:"), ImGui::Checkbox("##y: ", &_Y), 10.0f);

		curPos.x += 70.0f;
		ImGui::SetCursorPos(curPos);
		ImGui_SameLine(ImGui::Text("z:"), ImGui::Checkbox("##z: ", &_Z), 10.0f);

		m_CubeRotationAxis[0] = (float)_X;
		m_CubeRotationAxis[1] = (float)_Y;
		m_CubeRotationAxis[2] = (float)_Z;

		std::string sint = std::string("sin(" + std::to_string((int)glm::degrees(degree)) + "): ");
		std::string cost = std::string("cos(" + std::to_string((int)glm::degrees(degree)) + "): ");

		std::string sa = "sa";
		std::string ca = "ca";

		ImGui_SameLine(ImGui::Text((sa + " = " + sint).c_str()), ImGui::Text((ca + " = " + cost).c_str()), 50.0f);
		std::string line1 = ca + " + x^2 (1 - " + ca + ")    " + "   x y (1 - " + ca + ") - z " + sa + "    y " + sa + " x z (1 - " + ca + ")";
		std::string line2 = "z " + sa + " + x y (1 - " + ca + ")     " + ca + " y^2 (1 - " + ca + ")         -x " + sa + " y z (1 - " + ca + ")";
		std::string line3 = "-y " + sa + " + x z (1 - " + ca + ")    x " + sa + " y z (1 - " + ca + ")      " + ca + " z^2 (1 - " + ca + ")";
		
		drawMatrix(line1, line2, line3);

		glm::mat4 rotm = glm::mat4(1.0f);
		if (m_CubeRotationAxis != glm::vec3(0.0f))
			rotm = glm::rotate(glm::mat4(1.0f), degree, m_CubeRotationAxis);

		line1 = stringPrecision(rotm[0][0], 2) + "    " + stringPrecision(rotm[0][1], 2) + "    " + stringPrecision(rotm[0][2], 2);
		line2 = stringPrecision(rotm[1][0], 2) + "    " + stringPrecision(rotm[1][1], 2) + "    " + stringPrecision(rotm[1][2], 2);
		line3 = stringPrecision(rotm[2][0], 2) + "    " + stringPrecision(rotm[2][1], 2) + "    " + stringPrecision(rotm[2][2], 2);
		drawMatrix(line1, line2, line3, 450.0f, -65.0f);


		ImGui::End();

		break;
	}
	ImGui::SetNextWindowSize({ 300.0f, 60.0f });
	ImGui::SetNextWindowPos({ 1200.0f, 20.0f });
	ImGui::Begin("Selection", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	if (ImGui::BeginCombo("##tabsel", CurrentItemTab.c_str()))
	{
		bool itemSelected;

		if (ImGui::Selectable("Teorie", &itemSelected))
			m_CurrentTab = CurrentTab::Theory;

		ImGui::Separator();

		if (ImGui::Selectable("Aplicarea teoriei", &itemSelected))
			m_CurrentTab = CurrentTab::Application;
		ImGui::EndCombo();
	}

	ImGui::End();

	ImGui::SetNextWindowSize({ 1000.0f, 198.0f });
	ImGui::SetNextWindowPos({ 0.0f, 900.0f - 198.0f });
	ImGui::Begin("Circle", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	auto curPos = ImGui::GetCursorPos();
	curPos.x += 300.0f;
	curPos.y += 40.0f;

	ImGui::SetCursorPos(curPos);
	ImGui::PushItemWidth(150.0f);
	if (ImGui::BeginCombo("##grrd", CurrentItemLayer.c_str()))
	{
		bool itemSelected;

		if (ImGui::Selectable("Grade", &itemSelected))
			m_CurrentLayer = CircleLayer::Degrees;
		
		ImGui::Separator();

		if (ImGui::Selectable("Radiani", &itemSelected))
			m_CurrentLayer = CircleLayer::Radians;
		ImGui::EndCombo();
	}

	curPos = ImGui::GetCursorPos();
	curPos.x += 500.0f;
	curPos.y -= 35.0f;

	ImGui::SetCursorPos(curPos);
	ImGui::Text(("cos(" + std::to_string((int)glm::degrees(degree)) + "): " + std::to_string(std::cos(angle))).c_str());

	curPos.y += 20.0f;
	ImGui::SetCursorPos(curPos);
	ImGui::Text(("sin(" + std::to_string((int)glm::degrees(degree)) + "): " + std::to_string(std::sin(-angle))).c_str());

	ImGui::End();
}

void Circle::drawMatrix(const std::string& l1, const std::string& l2, const std::string& l3, int xoffset, int yoffset)
{
	auto curPos = ImGui::GetCursorPos();
	curPos.x += xoffset;
	curPos.y += yoffset;
	auto begCurPos = curPos;

	ImGui::SetCursorPos(curPos);
	ImGui::Text(l1.c_str());

	curPos.y += 20.0f;
	curPos.x = begCurPos.x;
	ImGui::SetCursorPos(curPos);
	ImGui::Text(l2.c_str());

	curPos.y += 20.0f;
	curPos.x = begCurPos.x;
	ImGui::SetCursorPos(curPos);
	ImGui::Text(l3.c_str());
}
