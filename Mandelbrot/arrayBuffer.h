#pragma once

#include <GL/glew.h>

class ArrayBuffer {
private:
	GLuint m_bufferId;
	GLuint m_componentCount;

public:
	ArrayBuffer(GLfloat *data, GLuint count, GLuint componentCount) {
		m_componentCount = componentCount;

		glGenBuffers(1, &m_bufferId);
		bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
		unbind();
	}

	~ArrayBuffer() {
		glDeleteBuffers(1, &m_bufferId);
	}

	void subData(GLushort *data, GLuint count) {
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data) * count, data);
		unbind();
	}

	void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); }
	void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	inline GLuint getComponentCount() { return m_componentCount; }
};