#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &bufferID); ASSESS_LINE;
	glBindBuffer(GL_ARRAY_BUFFER, bufferID); ASSESS_LINE;
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); ASSESS_LINE;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &bufferID);
}


void VertexBuffer::Bind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID); ASSESS_LINE;
}

void VertexBuffer::Unbind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); ASSESS_LINE;
}
