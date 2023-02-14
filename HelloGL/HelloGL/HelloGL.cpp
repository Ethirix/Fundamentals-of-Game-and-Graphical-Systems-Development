#include "HelloGL.h"
#include "GLUTCallbacks.h"

int main(int argc, char* argv[])
{
	HelloGL* window = new HelloGL(argc, argv);

	return 0;
}

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitWindowSize(800, 800);

	glutCreateWindow("First OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawPolygon();
	
	glFlush();
}

void HelloGL::DrawPolygon()
{
	//Scalene triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.9, 0.9);
		glVertex2f(-0.85, 1.0);
		glVertex2f(-0.75, 0.9);
		glEnd();
	}

	//Isosceles triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.75, 0.8);
		glVertex2f(-0.7, 1.0);
		glVertex2f(-0.65, 0.8);
		glEnd();
	}

	//Equilateral triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.65, 0.7);
		glVertex2f(-0.45, 1.0);
		glVertex2f(-0.25, 0.7);
		glEnd();
	}

	//Acute triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.25, 0.9);
		glVertex2f(-0.225, 1);
		glVertex2f(-0.15, 0.9);
		glEnd();
	}

	//Right-angle triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-1.0, 1.0);
		glVertex2f(-1.0, 0.9);
		glVertex2f(-0.9, 0.9);
		glEnd();
	}

	//Obtuse triangle
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.15, 1);
		glVertex2f(-0.05, 0.8);
		glVertex2f(0.2, 0.8);
		glEnd();
	}

	DrawShape(CreateShape(8, (360/16) * (3.14159265358979323846/180)));
}

void HelloGL::DrawShape(Shape::Shape shape)
{
	for (Shape::Polygon const &p : shape.Polygons)
	{
		glBegin(GL_POLYGON);
		for (int i = 0; i < 3; i++)
		{
			glVertex2f(p.Vertices[i].X, p.Vertices[i].Y);
		}
		glEnd();
	}
}

Shape::Shape HelloGL::CreateShape(int n, float angle)
{
	float angleIncrease = 2.0f * 3.14159265358979323846 / n;

	Shape::Shape shape;

	for (int i = 0; i < n; i++)
	{
		shape.Polygons.push_back(
			Shape::Polygon(
				Shape::Vertex2D(0, 0),
				Shape::Vertex2D(0 + 0.2 * cos(angle), 0 + 0.2 * sin(angle)),
				Shape::Vertex2D(0 + 0.2 * cos(angle + angleIncrease), 0 + 0.2 * sin(angle + angleIncrease))
			)
		);
		angle += angleIncrease;
		
	}

	return shape;
}