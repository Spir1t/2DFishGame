#pragma once
#include <GL/glut.h>
#include <Vector>


struct MyPolygon
{
	GLfloat X1;
	GLfloat Y1;
	GLfloat X2;
	GLfloat Y2;
	GLfloat X3;
	GLfloat Y3;
	GLfloat Red;
	GLfloat Green;
	GLfloat Blue;
};


struct Body
{
	std::vector<MyPolygon> Polygons;
};


class Fish
{
public:
	void Draw(GLfloat Light);
	void Move(GLfloat dx, GLfloat dy);

	GLfloat X;
	GLfloat Y;
	int Direction = 1;
	Body Body;
};


class GoldenFish : public Fish
{
public:
	GoldenFish();
};


class HunterFish : public Fish
{
	HunterFish();
};