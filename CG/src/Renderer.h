#ifndef MY_RENDERER_CONSTANT
#define MY_RENDERER_CONSTANT

#include "OpenglDebugger.h"
#include "VertexArrayObject.h"
#include "Shaders.h"
#include "Texture.h"
#include "Shapes.h"


class Renderer
{
public:
	void Clear()const;
	void Draw(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int offset = 0);
	void Draw(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int count, unsigned int offset);
	void Draw(const VertexArrayObject& va, const VertexBuffer& vb, const unsigned int& count, unsigned int offset =0);
	void DrawPoint(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int count, unsigned int offset);
	void DrawPoint(const VertexArrayObject& va, const VertexBuffer& vb, unsigned int count = 1, unsigned int offset = 0);	
};
#endif // !MY_RENDERER_CONSTANT
