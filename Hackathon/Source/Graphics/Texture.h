#pragma once
#include <string>

struct Texture
{
	Texture() = default;
	Texture(const std::string& filepath);
	~Texture();
	
	unsigned int TextureID;
};