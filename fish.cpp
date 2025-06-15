#include "fish.h"

void Fish::Draw(GLfloat Light)
{
	glEnd();
	for (MyPolygon &Polygon : Body.Polygons)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(Polygon.Red * Light, Polygon.Green * Light, Polygon.Blue * Light);
		glVertex2f(Direction * Polygon.X1 + X, Polygon.Y1 + Y);
		glVertex2f(Direction * Polygon.X2 + X, Polygon.Y2 + Y);
		glVertex2f(Direction * Polygon.X3 + X, Polygon.Y3 + Y);
		glEnd();
	}
}

void Fish::Move(GLfloat dx, GLfloat dy)
{
	if (dx > 0)
	{
		Direction = 1;
	}
	else if (dx < 0)
	{
		Direction = -1;
	}
	X += dx;
	Y += dy;
}

GoldenFish::GoldenFish()
{
	MyPolygon LowerBody = { -0.075, 0.05,
							-0.075, -0.05,
							0.075, -0.05,
							1, 165.0 / 250, 0 };
	
	MyPolygon UpperBody = { -0.075, 0.05,
							0.075, 0.05,
							0.075, -0.05,
							1, 165.0 / 250, 0 };
	
	MyPolygon Beak = { 0.075, 0.05,
						0.075, -0.05,
						0.125, 0,
						1, 165.0 / 250, 0 };
	
	MyPolygon Tail = { -0.075, 0,
						-0.125, 0.05,
						- 0.125, -0.05,
						1, 165.0 / 250, 0 };

	MyPolygon UpperEye = { 0.0625, 0.0125,
							0.0625, -0.0125,
							0.0875, -0.0125,
							0, 0, 0 };

	MyPolygon LowerEye = { 0.0875, 0.0125,
							0.0625, 0.0125,
							0.0875, -0.0125,
							0, 0, 0 };

	MyPolygon Fin = { -0.025, 0.1,
						-0.025, 0.05,
						0.025, 0.05,
						1, 165.0 / 250, 0 };
							
	Body.Polygons.push_back(LowerBody);
	Body.Polygons.push_back(UpperBody);
	Body.Polygons.push_back(Beak);
	Body.Polygons.push_back(Tail);
	Body.Polygons.push_back(UpperEye);
	Body.Polygons.push_back(LowerEye);
	Body.Polygons.push_back(Fin);
}