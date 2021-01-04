#include "Shapes.h"

Triangle::Triangle(float length)
{
	CreateVertices(3);
	Set(-(length / 2), (length / 2), 0, 0.0f, 1.0f);	// top-left
	Set((length / 2), (length / 2), 0, 1.0f, 1.0f);	// top-right
	Set(-(length / 2), -(length / 2), 0, 0.0f, 0.0f);	// bottom-left
}
Square::Square(float length)
{
	CreateVertices(4);
	Set( -(length / 2), (length / 2), 0, 0.0f, 1.0f);	// top-left
	Set(  (length / 2), (length / 2), 0, 1.0f, 1.0f);	// top-right
	Set(-(length / 2), -(length / 2), 0, 0.0f, 0.0f);	// bottom-left
	Set( (length / 2), -(length / 2), 0, 1.0f, 0.0f);	// bottom-right
}

Cube::Cube(float length) 
{
	CreateVertices(4 * 6);
	// front
	Set ( -(length / 2),  (length / 2), length / 2, 0.0f, 1.0f);	// top-left
	Set (  (length / 2),  (length / 2), length / 2, 1.0f, 1.0f);	// top-right
	Set( -(length / 2), -(length / 2), length / 2, 0.0f, 0.0f);	// bottom-left
	Set(  (length / 2), -(length / 2), length / 2, 1.0f, 0.0f);	// bottom-right

	// back
	Set(  (length / 2),  (length / 2), -length / 2, 0.0f, 1.0f);	// top-left
	Set( -(length / 2),  (length / 2), -length / 2, 1.0f, 1.0f);	// top-right
	Set(  (length / 2), -(length / 2), -length / 2, 0.0f, 0.0f);	// bottom-left
	Set( -(length / 2), -(length / 2), -length / 2, 1.0f, 0.0f);	// bottom-right

	// left
	Set( -(length / 2),  (length / 2), -length / 2, 0.0f, 1.0f);	// top-left
	Set( -(length / 2),  (length / 2),  length / 2, 1.0f, 1.0f);	// top-right
	Set( -(length / 2), -(length / 2), -length / 2, 0.0f, 0.0f);	// bottom-left
	Set( -(length / 2), -(length / 2),  length / 2, 1.0f, 0.0f);	// bottom-right

	// right
	Set(  (length / 2),  (length / 2),  length / 2, 0.0f, 1.0f);	// top-left
	Set(  (length / 2),  (length / 2), -length / 2, 1.0f, 1.0f);	// top-right
	Set(  (length / 2), -(length / 2),  length / 2, 0.0f, 0.0f);	// bottom-left
	Set(  (length / 2), -(length / 2), -length / 2, 1.0f, 0.0f);	// bottom-right

	// top
	Set( -(length / 2),  (length / 2), -length / 2, 0.0f, 1.0f);	// top-left
	Set(  (length / 2),  (length / 2), -length / 2, 1.0f, 1.0f);	// top-right
	Set( -(length / 2),  (length / 2),  length / 2, 0.0f, 0.0f);	// bottom-left
	Set(  (length / 2),  (length / 2),  length / 2, 1.0f, 0.0f);	// bottom-right

	// bottom
	Set(  (length / 2), -(length / 2), -length / 2, 0.0f, 1.0f);	// top-left
	Set( -(length / 2), -(length / 2), -length / 2, 1.0f, 1.0f);	// top-right
	Set(  (length / 2), -(length / 2),  length / 2, 0.0f, 0.0f);	// bottom-left
	Set( -(length / 2), -(length / 2),  length / 2, 1.0f, 0.0f);	// bottom-right

}

Sphere::Sphere(float radius, int longitude, int latitude) : radius(radius), longitude(longitude), latitude(latitude)
{
	CreateVertices(latitude * longitude);

	/* Spherical Coordinates (r,u,v)
	   x = r * cos(u) * cos(v)      y = r * cos(u) * sin(v)      z = r * sin(u)
	   
	   u: 2 * pi / angle,  where angle (-90 <= u <= 90)
	   v: -pi / angle angle (0 <= v <= 360)
	*/
	float u, v;
	float x, y, z;
	float deltaTheta = -glm::pi<float>() * 2.0f / (longitude - (2*longitude/latitude)); // to incriment pi, but stay within range
	float deltaPhi = glm::pi<float>() / latitude;
	
	for (unsigned i = 0; i <= latitude; i++) // number of stacks
	{
		u = glm::pi<float>()/2.0f + (i) * deltaTheta ;					// from -90 <= u <= 90
		z = radius * sinf(u);					   

		// first vertice = last vertices
		// Same position, but different texture coords
		for (unsigned int j = 0; j <= longitude; j++)
		{
			v = j * deltaPhi;

			x = radius * cosf(u) * cosf(v);
			y = radius * cosf(u) * sinf(v);
			
			Set(x, y, z, 1.0f - (float)j / longitude, (float)i / (latitude-2));
		}
	}
	for(int i = 0; i < longitude*5; i++)
		vertices.pop_back();
	Index();
 }

inline void Sphere::Set(float x, float y, float z, float texturePosX, float texturePosY)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back( texturePosX);
	vertices.push_back(texturePosY);
}
inline void Sphere::Set(std::vector<float>& vector, float x, float y, float z, float texturePosX, float texturePosY)
{
	vector.push_back(x);
	vector.push_back(y);
	vector.push_back(z);
	vector.push_back(texturePosX);
	vector.push_back(texturePosY);
}


inline void Sphere::Index()
{

	const unsigned int stride = longitude + 1; // first point = last point, but with different texture positions
	
	//index into triangles
	for (unsigned int i = 0, index = 0;   i < latitude-2;     i++)
	{
		// latitude +1 points
		for (unsigned int j = 0; j < longitude; j++)
		{
			// longitude +1 points
			// divide into 2 trinangles


			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + stride);

			indices.push_back(index + 1);
			indices.push_back(index + 1 + stride);
			indices.push_back(index + stride);

			index++;

		}
		index++;
		
	}
}