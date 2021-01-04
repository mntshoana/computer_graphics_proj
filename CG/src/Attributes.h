#ifndef ATTRIBUTES_CONSTANT
#define ATTRIBUTES_CONSTANT

#include "OpenglDebugger.h"

class Element
{
public:
	unsigned int count;
	GLenum type;
	GLboolean normalized;
	const unsigned int getSize()const // Size in bytes
	{
		switch (type)
		{
			case GL_FLOAT:	return count * sizeof(float); // bytes
			default:		 ASSERT(false); // type not supported yet
							return 0;
		}
	}
};

class Attribute
{
private:
	std::vector<Element> elements;
    unsigned int stride;

public:
	Attribute() : stride(0) {}
	
	const std::vector<Element> getElements()const   { return elements; }	
	const unsigned int getStride()const { return stride; }

	template <typename T>  
	void push(unsigned int count)	{ ASSERT(false); } // Restrict unsupported types for now
	
	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back({count, GL_FLOAT, GL_FALSE });
		stride += count * sizeof(float);
	}
};


#endif // !ATTRIBUTES_CONSTANT
