#include "Mesh.h"

Mesh::Mesh(const std::string& path)
{
	LoadFromTXT(path);
}