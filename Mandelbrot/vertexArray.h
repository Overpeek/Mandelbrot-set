#pragma once

#include <GL/glew.h>
#include <vector>
#include "arrayBuffer.h"

class VertexArray {
private:
	GLuint m_arrayId;
	std::vector<ArrayBuffer*> m_buffers;

public:
	VertexArray() {
		glGenVertexArrays(1, &m_arrayId);
		bind();
	}

	~VertexArray() {
		for (ArrayBuffer *b : m_buffers)
		{
			delete b;
		}
		glDeleteVertexArrays(1, &m_arrayId);
	}

	void addBuffer(ArrayBuffer *buffer, GLuint index) {
		bind();
		m_buffers.push_back(buffer);
		buffer->bind();

		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);

		buffer->unbind();
		unbind();
	}

	void bind() { glBindVertexArray(m_arrayId); }
	void unbind() { glBindVertexArray(0); }
};