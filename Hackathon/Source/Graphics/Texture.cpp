#include "Texture.h"

#include "std_image.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Texture::Texture(const std::string& filepath)
{
    int width, height, bbp;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* texData = nullptr;
    texData = stbi_load(filepath.c_str(), &width, &height, &bbp, 0);

    unsigned int internalFormat = 0, Format = 0;
    if (bbp == 3) {
        internalFormat = GL_RGB8;
        Format = GL_RGB;
    }

    else if (bbp == 4) {
        internalFormat = GL_RGBA8;
        Format = GL_RGBA;
    }

    else if (bbp == 1)
    {
        internalFormat = GL_RGBA;
        Format = GL_RED;
    }

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, Format, GL_UNSIGNED_BYTE, texData);

    stbi_image_free(texData);
}

Texture::~Texture()
{
    glDeleteTextures(1, &TextureID);
}
