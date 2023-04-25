#include "Texture2D.h"

Texture2D::Texture2D(const Texture2D& texture2D)
{
	_id = texture2D.GetID();
	_width = texture2D.GetWidth();
	_height = texture2D.GetHeight();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_id);
}

unsigned Texture2D::GetID() const
{
	return _id;
}

unsigned Texture2D::GetWidth() const
{
	return _width;
}

unsigned Texture2D::GetHeight() const
{
	return _height;
}

//private
Texture2D::Texture2D(const unsigned id, const unsigned width, const unsigned height)
{
	_id = id;
	_width = width;
	_height = height;
}

