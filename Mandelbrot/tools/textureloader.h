#pragma once

#include <string>
#include <GL/glew.h>

namespace tools {

	class TextureLoader {
	public:
		static GLuint loadTexture(std::string filepath, GLenum format);
	};

}