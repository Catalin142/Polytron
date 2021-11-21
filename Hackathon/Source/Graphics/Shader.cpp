#include "Shader.h"
#include "Filesystem/File.h"

#include "GL/glew.h"

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
	ShaderID = glCreateProgram();

	unsigned int vertexShader;
	unsigned int fragmentShader;

	vertexShader = compileShader(GL_VERTEX_SHADER, vertex);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(ShaderID, vertexShader);
	glAttachShader(ShaderID, fragmentShader);

	glLinkProgram(ShaderID);
	glValidateProgram(ShaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& path)
{
	unsigned int id = glCreateShader(type);

	std::string shaderCode = getFileContent(path);
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(id, 1, &shaderSource, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)_malloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

std::unordered_map<std::string, std::unique_ptr<Shader>> ShaderManager::Shaders;

void ShaderManager::addShader(const std::string& name, const std::string& vertex, const std::string& fragemnt)
{
	Shaders[name] = std::make_unique<Shader>(vertex, fragemnt);
}

void ShaderManager::deleteShader(const std::string& name)
{
	Shaders.erase(name);
}
