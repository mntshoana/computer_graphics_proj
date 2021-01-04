


#ifndef SOLAR3D_H_
#define SOLAR3D_H_
#include <pch.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/vec4.hpp>
#define NumPlanet 9
typedef glm::vec4 point4;
typedef glm::vec4 color4;

void timer(int p);
void keyboard(unsigned char k, int x, int y);

const int NumTimesToSubdivide = 5;
const int NumTriangles        = 4096;  // (4 faces)^(NumTimesToSubdivide + 1)
const int NumVertices         = 3 * NumTriangles;

GLfloat yaw    = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch  =  0.0f;

glm::vec3 cameraPos   = glm::vec3(0.0, -5.0,  40.0);
glm::vec3 cameraFront = glm::vec3(0.0, 1.0, -8.0);
glm::vec3 cameraUp    = glm::vec3(0.0, 1.0,  0.0);

glm::vec3 initCameraPos = cameraPos;

point4 points[NumVertices + 6];
glm::vec3   normals[NumVertices];

glm::mat4 modelView[NumPlanet];
GLubyte** imageGeneral;
int width[NumPlanet+1], height[NumPlanet+1];
int old_x, old_y, valid=0, firstMouse = 1, mouseX, mouseY, Index = 0;;

double changeUnit = 0, lastZoom, rotationSpeed = 90, lastSpeed = rotationSpeed, initSpeed = rotationSpeed;

bool projection = true, follow = false, lighting = false, isFullScreen = false;

double sunTurn[NumPlanet], ownTurn[NumPlanet], inclination[NumPlanet], translate[NumPlanet],
		radiuses[NumPlanet], distances[NumPlanet], rotationsOverSun[NumPlanet];
const char* textureNames[NumPlanet + 1];

enum { Xaxis = 0,
	Yaxis = 1,
	Zaxis = 2,
	NumAxes = 3 };



GLfloat Theta[NumAxes] = { -90, 0, 0 };

int Axis = Xaxis, anim_count = 0, anim = 0, lastSelection = -1, index = -1;
// Model-view and projection matrices uniform location
#endif
