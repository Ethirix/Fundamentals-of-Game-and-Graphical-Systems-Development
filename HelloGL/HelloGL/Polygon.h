#pragma once
#include "Vertex2D.h"
namespace Shape
{
	struct Polygon
	{
		Polygon(Vertex2D a, Vertex2D b, Vertex2D c);

		Vertex2D Vertices[3];
	};
}


