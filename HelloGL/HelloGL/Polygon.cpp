#include "Polygon.h"

namespace Shape
{
	Polygon::Polygon(Vertex2D a, Vertex2D b, Vertex2D c)
	{
		Vertices[0] = a;
		Vertices[1] = b;
		Vertices[2] = c;
	}
}