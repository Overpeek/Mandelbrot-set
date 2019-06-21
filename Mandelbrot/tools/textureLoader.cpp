#include "textureloader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <string>
#include <fstream>


namespace tools {

	GLuint TextureLoader::loadTexture(std::string filepath, GLenum format)
	{
		int width, height, nrChannels;
		GLubyte *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
		if (!data) return 0;

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_1D, texture);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_1D);

		stbi_image_free(data);
	}

}