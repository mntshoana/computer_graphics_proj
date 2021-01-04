#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : count(count)
{
	glGenBuffers(1, &bufferID); ASSESS_LINE;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); ASSESS_LINE;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); ASSESS_LINE;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); ASSESS_LINE;
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); ASSESS_LINE;
}

unsigned int IndexBuffer::GetCount() const
{
	return count;
}
