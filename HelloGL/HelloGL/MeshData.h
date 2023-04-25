#pragma once

template<class T>
class MeshData
{
public:
	MeshData() = default;

	~MeshData()
	{
		delete[] Index;
	}

	T* Index;
	unsigned IndexLength = 0;
};