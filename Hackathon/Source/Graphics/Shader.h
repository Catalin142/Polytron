#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();

	unsigned int ShaderID;

private:
	unsigned int compileShader(unsigned int type, const std::string& path);
};

class ShaderManager
{
public:
	static void addShader(const std::string& name, const std::string& vertex, const std::string& fragemnt);
	static void deleteShader(const std::string& name);

	static std::unordered_map<std::string, std::unique_ptr<Shader>> Shaders;
};
