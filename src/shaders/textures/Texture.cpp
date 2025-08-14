#include "Application.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char *tex_file, unsigned int type)
{
	stbi_set_flip_vertically_on_load(true);
	this->data = stbi_load(tex_file, &this->witdh, &this->height, &this->nrChannels, 0);
	if (this->data)
	{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, witdh, height, 0, type, GL_UNSIGNED_BYTE, data);	
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Cloud not open a texture\n";
		glfwTerminate();
	}
}

bool	Texture::Error()
{
	if (this->data)
		return (false);
	return (true);
}
