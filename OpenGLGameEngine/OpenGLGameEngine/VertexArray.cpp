#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_Buffers.size(); i++)
		delete m_Buffers[i];
}

void VertexArray::addBuffer(Buffer* Buffer, GLuint index, GLsizei stride, int offset)
{
	bind();
	Buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, Buffer->getComponentCount(), GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));

	Buffer->unbind();
	unbind();
}

void VertexArray::addBuffer(Buffer* Buffer, GLuint index)
{
	bind();
	Buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, Buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	Buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
