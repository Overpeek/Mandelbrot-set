#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Shader {
private:
	GLuint m_shaderID;

public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	void enable();
	void disable();

	inline GLint getUniformLocation(std::string name) { return glGetUniformLocation(m_shaderID, name.c_str()); }

	inline void setUniform1i(std::string name, int value) { glUniform1i(getUniformLocation(name), value); }
	inline void setUniform2i(std::string name, glm::ivec2 value) { glUniform2i(getUniformLocation(name), value.x, value.y); }
	inline void setUniform3i(std::string name, glm::ivec3 value) { glUniform3i(getUniformLocation(name), value.x, value.y, value.y); }
	inline void setUniform4i(std::string name, glm::ivec4 value) { glUniform4i(getUniformLocation(name), value.x, value.y, value.y, value.w); }

	inline void setUniform1f(std::string name, float value) { glUniform1f(getUniformLocation(name), value); }
	inline void setUniform2f(std::string name, glm::fvec2 value) { glUniform2f(getUniformLocation(name), value.x, value.y); }
	inline void setUniform3f(std::string name, glm::fvec3 value) { glUniform3f(getUniformLocation(name), value.x, value.y, value.y); }
	inline void setUniform4f(std::string name, glm::fvec4 value) { glUniform4f(getUniformLocation(name), value.x, value.y, value.y, value.w); }

	inline void setUniform1d(std::string name, double value) { glUniform1d(getUniformLocation(name), value); }
	inline void setUniform2d(std::string name, glm::dvec2 value) { glUniform2d(getUniformLocation(name), value.x, value.y); }
	inline void setUniform3d(std::string name, glm::dvec3 value) { glUniform3d(getUniformLocation(name), value.x, value.y, value.y); }
	inline void setUniform4d(std::string name, glm::dvec4 value) { glUniform4d(getUniformLocation(name), value.x, value.y, value.y, value.w); }

	inline void setUniformMat4(std::string name, glm::mat4 value) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }

};