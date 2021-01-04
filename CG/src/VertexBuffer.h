#ifndef MY_VERTEX_BUFFER
#define MY_VERTEX_BUFFER

#include "OpenglDebugger.h"

class VertexBuffer {
private:
	unsigned int bufferID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};
#endif