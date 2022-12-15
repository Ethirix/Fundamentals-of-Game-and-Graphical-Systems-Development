#pragma once

#include "GameObject.h"

class Collidable
{
public:
	/**
	 * \brief Default Collidable Constructor using default values.
	 */
	Collidable() = default;
	/**
	 * \brief Creates a Collidable without a Trigger flag.
	 * \param selfObject A reference to the GameObject that a Collidable is attached to.
	 */
	Collidable(GameObject* selfObject);
	/**
	 * \brief Creates a Collidable with a defined Trigger flag.
	 * \param selfObject A reference to the GameObject that a Collidable is attached to.
	 * \param isATrigger The Trigger Flag.
	 */
	Collidable(GameObject* selfObject, bool isATrigger);
	virtual ~Collidable() = default;
	/**
	 * \brief Checks if two objects are colliding.
	 * \param objectToCheck GameObject to check the Collision against.
	 * \return If a Collision was Detected.
	 */
	bool IsCollided(const GameObject* objectToCheck);
	/**
	 * \brief Returns if the Collidable is a Trigger
	 * \return The isTrigger flag.
	 */
	bool IsTrigger();
	/**
	 * \brief Function that runs when a Collision is detected.
	 * \param collidedObject GameObject that the collision was with.
	 */
	virtual void OnCollision(GameObject* collidedObject);
	/**
	 * \brief Returns the Pointer of the GameObject the Collidable is attached to.
	 * \return Pointer of GameObject
	 */
	GameObject* GetSelf();
private:
	bool _isTrigger = false;
	GameObject* _self = nullptr;
};