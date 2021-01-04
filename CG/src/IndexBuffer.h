#ifndef MY_INDEX_BUFFER
#define MY_INDEX_BUFFER

#include "OpenglDebugger.h"

class IndexBuffer {
private:
	unsigned int bufferID;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;
};
#endif
