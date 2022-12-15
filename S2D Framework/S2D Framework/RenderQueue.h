#pragma once

#include <vector>
#include "GameObject.h"

class RenderQueue
{
public:
	/**
	 * \brief Default Constructor for RenderQueue.
	 */
	RenderQueue();
	/**
	 * \brief Creates a RenderQueue with a user defined Depth.
	 * \param depth Depth possible by the RenderQueue.
	 */
	explicit RenderQueue(int depth);

	/**
	 * \brief Adds a GameObject to the RenderQueue
	 * \param gameObject GameObject to be added to the Renderer.
	 */
	void Add(GameObject* gameObject);

	/**
	 * \brief Removes a GameObject from the RenderQueue.
	 * \param gameObject GameObject to be removed from the Renderer.
	 */
	void Remove(const GameObject* gameObject);

	/**
	 * \brief Gets the Size of the Queue.
	 * \return Queue size.
	 */
	int GetQueueSize();

	std::vector<GameObject*>* RndQueue;

private:
	int _queueSize;
};

