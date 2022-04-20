#include "Renderer.h"

#include "Graphics/Shader.h"

#include "glm/gtc/type_ptr.hpp"

VertexArray Renderer::m_QuadVertexArray;
VertexArray Renderer::m_LineVertexArray;
VertexArray Renderer::m_CubeVertexArray;

glm::mat4 Renderer::m_OrthographicMatrix;

glm::mat4 Renderer::m_ProjectionMatrix = glm::mat4(1.0f);
glm::mat4 Renderer::m_ViewMatrix = glm::mat4(1.0f);

unsigned int Renderer::m_Framebuffer;
unsigned int Renderer::m_ColorAttachment;

#include "GL/glew.h"

void Renderer::Init()
{
    // shaders
    ShaderManager::addShader("QuadShader", "Resources/Shaders/2DRenderer_vertex.glsl", "Resources/Shaders/2DRenderer_fragment.glsl");
    ShaderManager::addShader("LineShader", "Resources/Shaders/2DLine_vertex.glsl", "Resources/Shaders/2DLine_fragment.glsl");
    ShaderManager::addShader("CircleShader", "Resources/Shaders/2DCircle_vertex.glsl", "Resources/Shaders/2DCircle_fragment.glsl");
    ShaderManager::addShader("CubeShader", "Resources/Shaders/3DCube_vertex.glsl", "Resources/Shaders/3DCube_fragment.glsl");

    initLineArray();
    initQuadArray();
    initCubeArray();
}

void Renderer::beginScene(const glm::mat4& ortho)
{
    m_OrthographicMatrix = ortho;
}

void Renderer::drawQuad(unsigned int tex, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    auto& shader = ShaderManager::Shaders["QuadShader"];
    glUseProgram(shader->ShaderID);

    glBindVertexArray(m_QuadVertexArray.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVertexArray.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadVertexArray.indexBuffer);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "ortho"), 1, GL_FALSE, &m_OrthographicMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "model"), 1, GL_FALSE, &model[0][0]);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glUniform1i(glGetUniformLocation(shader->ShaderID, "tex"), 0);
    glUniform4f(glGetUniformLocation(shader->ShaderID, "color"), color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::drawCircle(const glm::vec2& position, float radius, float thickness, const glm::vec4& color)
{
    auto& shader = ShaderManager::Shaders["CircleShader"];
    glUseProgram(shader->ShaderID);

    glBindVertexArray(m_QuadVertexArray.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVertexArray.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadVertexArray.indexBuffer);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "ortho"), 1, GL_FALSE, &m_OrthographicMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "model"), 1, GL_FALSE, &model[0][0]);

    glUniform4f(glGetUniformLocation(shader->ShaderID, "color"), color.r, color.g, color.b, color.a);
    glUniform1f(glGetUniformLocation(shader->ShaderID, "thicknes"), thickness);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::drawLine(const glm::vec2& start, const glm::vec2& end, float thickness, const glm::vec4& color)
{
    float line[] = {
        start.x, start.y,
        end.x, end.y
    };

    auto& shader = ShaderManager::Shaders["LineShader"];
    glUseProgram(shader->ShaderID);

    glBindVertexArray(m_LineVertexArray.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_LineVertexArray.vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);

    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "ortho"), 1, GL_FALSE, &m_OrthographicMatrix[0][0]);
    glUniform4f(glGetUniformLocation(shader->ShaderID, "color"), color.r, color.g, color.b, color.a);

    glLineWidth(thickness);
    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

unsigned int Renderer::drawCube(const glm::vec3& position, const glm::vec3& size, float angle, const glm::vec3& rotation, const glm::vec4& color)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLineWidth(6.0f);

    glViewport(0, 0, 1000, 1000);

    auto& shader = ShaderManager::Shaders["CubeShader"];
    glUseProgram(shader->ShaderID);

    glBindVertexArray(m_CubeVertexArray.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_CubeVertexArray.vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CubeVertexArray.indexBuffer);

    glm::mat4 Rot = glm::mat4(1.0f);
    if (rotation != glm::vec3(0.0f))
        Rot = glm::rotate(glm::mat4(1.0f), angle, rotation);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * Rot *
        glm::scale(glm::mat4(1.0f), size);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "proj"), 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "view"), 1, GL_FALSE, &m_ViewMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->ShaderID, "model"), 1, GL_FALSE, &model[0][0]);

    glUniform4f(glGetUniformLocation(shader->ShaderID, "color"), color.r, color.g, color.b, color.a);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    glViewport(0, 0, 1600, 900);
    return m_ColorAttachment;
}

void Renderer::initQuadArray()
{
    float vert[] = {
         -1.0f, -1.0f, 0.0f, 0.0f,
          1.0f, -1.0f, 1.0f, 0.0f,
         -1.0f,  1.0f, 0.0f, 1.0f,
          1.0f,  1.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_QuadVertexArray.vertexArray);

    glGenBuffers(1, &m_QuadVertexArray.vertexBuffer);
    glGenBuffers(1, &m_QuadVertexArray.indexBuffer);

    glBindVertexArray(m_QuadVertexArray.vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVertexArray.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadVertexArray.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::initLineArray()
{
    glGenVertexArrays(1, &m_LineVertexArray.vertexArray);
    glGenBuffers(1, &m_LineVertexArray.vertexBuffer);
    glBindVertexArray(m_LineVertexArray.vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_LineVertexArray.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), NULL, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::initCubeArray()
{
    m_ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 100.0f);
    m_ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    float vert[] = {
        // Front face
        -1.0, -1.0, 1.0,
         1.0, -1.0, 1.0,
         1.0, 1.0, 1.0,
         -1.0, 1.0, 1.0,
         
         // Back face
         -1.0, -1.0, -1.0,
         -1.0, 1.0, -1.0,
         1.0, 1.0, -1.0,
         1.0, -1.0, -1.0,
         
         // Top face
         -1.0, 1.0, -1.0,
         -1.0, 1.0, 1.0,
         1.0, 1.0, 1.0,
         1.0, 1.0, -1.0,
         
         // Bottom face
         -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0, -1.0, 1.0,
         -1.0, -1.0, 1.0,
         
         // Right face
         1.0, -1.0, -1.0,
         1.0, 1.0, -1.0,
         1.0, 1.0, 1.0,
         1.0, -1.0, 1.0,
         
         // Left face
         -1.0, -1.0, -1.0,
         -1.0, -1.0, 1.0,
         -1.0, 1.0, 1.0,
         -1.0, 1.0, -1.0,
    };
    unsigned int indices[] = {
        0, 1, 2,      0, 2, 3,    
        4, 5, 6,      4, 6, 7,    
        8, 9, 10,     8, 10, 11,   
        12, 13, 14,   12, 14, 15, 
        16, 17, 18,   16, 18, 19, 
        20, 21, 22,   20, 22, 23, 
    };

    glGenVertexArrays(1, &m_CubeVertexArray.vertexArray);

    glGenBuffers(1, &m_CubeVertexArray.vertexBuffer);
    glGenBuffers(1, &m_CubeVertexArray.indexBuffer);

    glBindVertexArray(m_CubeVertexArray.vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_CubeVertexArray.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CubeVertexArray.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1000, 1000, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        __debugbreak();

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}