#pragma once
#include <string>
#include <fstream>
#include <iostream>

static std::string getFileContent(const std::string& filepath)
{
	std::string content;
	std::ifstream f(filepath.c_str(), std::ios::binary);

	if (!f.is_open())
	{
		std::cout << "Nu s-a gasit: " << filepath << std::endl;
		return "Error";
	}
	else
	{
		f.seekg(0, std::ios::end);
		content.resize(f.tellg());
		f.seekg(0, std::ios::beg);
		f.read(&content[0], content.size());
		f.close();
	}

	return content;
}