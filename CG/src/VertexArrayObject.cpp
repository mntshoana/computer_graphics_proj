#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &vaoID); ASSESS_LINE;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vaoID); ASSESS_LINE;
}

void VertexArrayObject::Bind()const
{
	glBindVertexArray(vaoID); ASSESS_LINE;
}

void VertexArrayObject::UnBind()const
{
	glBindVertexArray(0); ASSESS_LINE;
}

void VertexArrayObject::AddBuffers(const VertexBuffer& vb, const Attribute& attributes)
{
	this->Bind();
	// preparing current state of the scene
	vb.Bind(); // vertices

	// preparing attributes
	const auto& attrList = attributes.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attrList.size(); i++)
	{
		const auto& attr = attrList[i];
		glEnableVertexAttribArray(i); ASSESS_LINE;
		glVertexAttribPointer(i, attr.count, attr.type,
			                     attr.normalized, 
			                     attributes.getStride(), 
			                     (const float*)offset); ASSESS_LINE;
		offset += attr.getSize(); // update next attribute's offset
	}

}
