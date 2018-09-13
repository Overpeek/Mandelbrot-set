#include "shader.h"

#include "tools/filereader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	std::string vertexSourceStr = tools::readFile(vertexPath.c_str());
	const GLchar *vertexSourceChar = vertexSourceStr.c_str();
	std::string fragmentSourceStr = tools::readFile(fragmentPath.c_str());
	const GLchar *fragmentSourceChar = fragmentSourceStr.c_str();

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSourceChar, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSourceChar, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR 0: Vertex shader compilation failed!\n" << infoLog << std::endl;
		system("pause");
		exit(0);
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR 1: Fragment shader compilation failed!\n" << infoLog << std::endl;
		system("pause");
		exit(0);
	}

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	glLinkProgram(m_shaderID);

	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
		std::cout << "ERROR 2: Shader program linking failed!\n" << infoLog << std::endl;
		system("pause");
		exit(0);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::enable() {
	glUseProgram(m_shaderID);
}

void Shader::disable() {
	glUseProgram(0);
}