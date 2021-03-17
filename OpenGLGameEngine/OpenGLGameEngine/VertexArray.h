#pragma once

#include <vector>
#include <GL/glew.h>

#include "Buffer.h"
#include "IndexBuffer.h"

class VertexArray
{

private:

	GLuint m_ArrayID;
	std::vector<Buffer*> m_Buffers;

public:

	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* Buffer, GLuint index, GLsizei stride, int offset);
	void addBuffer(Buffer* Buffer, GLuint index);

	void bind() const;
	void unbind() const;
};

