#pragma once

#include <vector>
#include "GameObject.h"

class RenderQueue
{
public:
	RenderQueue();
	explicit RenderQueue(int depth);

	void Add(GameObject* gameObject);
	void Remove(const GameObject* gameObject);
	int GetQueueSize();

	std::vector<GameObject*>* RndQueue;

private:
	int _queueSize;
};

