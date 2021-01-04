#include "Renderer.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ASSESS_LINE;
}


void Renderer::Draw(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int offset)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount() - offset, GL_UNSIGNED_INT, static_cast<int*>(0) + offset); ASSESS_LINE;
}
void Renderer::Draw(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int count, unsigned int offset)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<unsigned int*>(0) + offset); ASSESS_LINE;
}

void Renderer::Draw(const VertexArrayObject& va, const VertexBuffer& vb, const unsigned int& count, const unsigned int offset)
{
	va.Bind();
	vb.Bind();
	glDrawArrays(GL_TRIANGLES,  offset, count); ASSESS_LINE;
}
void Renderer::DrawPoint(const VertexArrayObject& va, const VertexBuffer& vb, const IndexBuffer& ib, unsigned int count, unsigned int offset)
{
	va.Bind();
	vb.Bind();
	ib.Bind();
	glPointSize(2.0f);
	glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, static_cast<unsigned int*>(0) + offset); ASSESS_LINE;
}
void Renderer::DrawPoint(const VertexArrayObject& va, const VertexBuffer& vb, unsigned int count, unsigned int offset)
{
	va.Bind();
	vb.Bind();
	glPointSize(2.0f);
	glDrawArrays(GL_POINTS, offset, count); ASSESS_LINE;
}