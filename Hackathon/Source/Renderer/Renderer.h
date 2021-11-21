#pragma once
#include <memory>
#include "Graphics/Texture.h"
#include "glm/glm.hpp"

struct VertexArray
{
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
};

class Renderer
{
public:
	static void Init();

	static void beginScene(const glm::mat4& ortho);

	static void drawQuad(unsigned int tex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	static void drawCircle(const glm::vec2& position, float radius, float thicknes = 1.0f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	static void drawLine(const glm::vec2& start, const glm::vec2& end, float thickness = 0.1f, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	static unsigned int drawCube(const glm::vec3& position, const glm::vec3& size, float angle, const glm::vec3& rotation, const glm::vec4& color);

private:
	Renderer() = default;
	~Renderer() = default;

	static VertexArray m_QuadVertexArray;
	static VertexArray m_LineVertexArray;
	static VertexArray m_CubeVertexArray;

	static glm::mat4 m_OrthographicMatrix;

	static glm::mat4 m_ProjectionMatrix;
	static glm::mat4 m_ViewMatrix;

	static unsigned int m_Framebuffer;
	static unsigned int m_ColorAttachment;

	static void initQuadArray();
	static void initLineArray();
	static void initCubeArray();
};
