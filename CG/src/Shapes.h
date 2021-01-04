#ifndef MY_SHAPE_CONSTANT
#define MY_SHAPE_CONSTANT

#include "pch.h"

class Shape {
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
protected:
	unsigned int count;
public:
	virtual int getVertexCount() const { return count; }
	virtual int getIndexCount() const { return indices.size(); }
	virtual int getVertexSizeb() const { return 5 * count * sizeof(float); }
public:
	virtual int getIndexSizeb() const { return indices.size() * sizeof(unsigned int); }

	void CreateVertices(unsigned int size)
	{
		count = size;
		vertices.reserve(size);
		indices.reserve(size);
	}

	virtual inline void Set(float x, float y, float z, float texturePosX, float texturePosY)
	{
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
		vertices.push_back(texturePosX);
		vertices.push_back(texturePosY);
		
		//index into triangles
		static unsigned int index;
		if (indices.size() == 0)
			index = 0;

		if (index != 0 && (index + 1) % 4 == 0 && count % 4 == 0) // Divides count == 4 corners into 2 triangles
		{
			indices.push_back(index - 2);
			indices.push_back(index - 1);
			indices.push_back(index);
		}
		else if (index != 0 && index == 4 && count == 5) //  Divides count == 5 corners into 3 triangles
		{
			indices.push_back(index - 2);
			indices.push_back(index - 1);
			indices.push_back(index);
		}
		else
			indices.push_back(index);
		index++;
	}
};

class Triangle : public Shape
{
public:
	Triangle(float length);
};

class Square : public Shape
{
public:
	Square(float length);
};

class Cube : public Shape 
{
public:
	Cube(float length);
};

class Sphere : public Shape //UV Sphere
{
public:
	Sphere(float radius, int longitude = 36, int latitude = 18);

	unsigned int latitude;
	unsigned int longitude;
	float radius;

	virtual inline void Set(float x, float y, float z, float texturePosX, float texturePosY) override;
	virtual inline void Set(std::vector<float>& vector, float x, float y, float z, float texturePosX, float texturePosY);
private:

	virtual inline void Index();
	
};
#endif