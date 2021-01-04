#ifndef VERTEX_ARRAY_OBJECT
#define VERTEX_ARRAY_OBJECT

#include "OpenglDebugger.h"
#include "VertexBuffer.h"
#include "Attributes.h"
#include "IndexBuffer.h"

class VertexArrayObject
{
private: unsigned int vaoID;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind()const;
	void UnBind()const;
	void AddBuffers(const VertexBuffer& vb, const Attribute& attr);
	void AddBuffers(const VertexBuffer& vb, const Attribute& attr, const IndexBuffer& ib);

};
#endif // !VERTEX_ARRAY_OBJECT
