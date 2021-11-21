#pragma once
#include <unordered_map>

#include "Renderer/Renderer.h"
#include "System/Input.h"
#include "Graphics/Texture.h"

enum class CircleLayer
{
	Degrees,
	Radians,

	Radians4,
	Degrees4,
	
	Radians12,
	Degrees12,
};

enum class CurrentTab
{
	Theory,
	Application,
};

class Circle 
{
public:
	Circle();
	void Update(float deltaTime);

	CurrentTab m_CurrentTab = CurrentTab::Theory;
private:
	glm::vec2 m_CirclePosition = { 500.0f, 550.0f };
	float m_CircleRadius = 250.0f;

	std::unordered_map<CircleLayer, std::shared_ptr<Texture>> m_Layers;

	std::vector<std::shared_ptr<Texture>> m_Text;
	int m_CurrentSlide = 0;
	float m_ChangeCooldown = 1.0f;
	float m_LastChange = 0.0f;

	CircleLayer m_CurrentLayer = CircleLayer::Degrees; 

	glm::vec3 m_CubeRotationAxis = glm::vec3(1.0f, 1.0f, 1.0f);

	void drawMatrix(const std::string& l1, const std::string& l2, const std::string& l3, int xoffset = 0.0f, int yoffset = 0.0f);
};