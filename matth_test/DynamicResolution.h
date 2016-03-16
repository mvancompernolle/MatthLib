#pragma once

#include "CollisionSystem.h"
#include "matth.h"

class DynamicResolution : public CollisionSystem {
	bool condition( Collision c ) {
		return c.first->rigidbody > -1 && c.second->rigidbody > -1;
	}

	void update(Collision c) {
		matth::vec2 mtv = c.collisionData.normal * c.collisionData.depth;
		matth::vec2 p1 = c.first->transform->getPos() - mtv/2.0f;
		matth::vec2 p2 = c.second->transform->getPos() + mtv/2.0f;
		c.first->transform->setPos( p1 );
		c.second->transform->setPos( p2 );
		std::swap( c.first->rigidbody->vel, c.second->rigidbody->vel );
	}
};