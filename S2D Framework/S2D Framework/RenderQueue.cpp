#include "RenderQueue.h"

RenderQueue::RenderQueue()
{
	_queueSize = 16;
	RndQueue = new std::vector<GameObject*>[_queueSize];
}

RenderQueue::RenderQueue(int depth)
{
	_queueSize = depth;
	RndQueue = new std::vector<GameObject*>[depth];
}

void RenderQueue::Add(GameObject* gameObject)
{
	int rndDepth = gameObject->GetRenderDepth();

	if (rndDepth >= _queueSize)
		rndDepth = _queueSize - 1;
	
	if (rndDepth < 0)
		rndDepth = 0;
	

	RndQueue[rndDepth].push_back(gameObject);
}

void RenderQueue::Remove(const GameObject* gameObject)
{
	for (int i = 0; i < _queueSize; i++)
	{
		for (int j = 0; j < RndQueue[i].size(); j++)
		{
			if (RndQueue[i][j] == gameObject)
				RndQueue[i].erase(RndQueue[i].begin() + j);
		}
	}
}

int RenderQueue::GetQueueSize()
{
	return _queueSize;
}

