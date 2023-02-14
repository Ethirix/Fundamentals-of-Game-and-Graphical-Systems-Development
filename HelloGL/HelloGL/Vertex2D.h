#pragma once

namespace Shape
{
	struct Vertex2D
	{
		Vertex2D() = default;
		Vertex2D(float x, float y);

		float X;
		float Y;
	};
}