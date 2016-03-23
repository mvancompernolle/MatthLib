#pragma once

#include "CollisionSystem.h"
#include "matth.h"

class DynamicResolution : public CollisionSystem {
	bool condition( Collision c ) {
		return c.first->rigidbody > -1 && c.second->rigidbody > -1;
	}

	void update(Collision c) {
		if ( c.collisionData.wasCollision ) {
			matth::vec2 mtv = c.collisionData.normal * c.collisionData.depth;
			std::cout << "depth: " << c.collisionData.depth 
				<< " normal: " << c.collisionData.normal.x << ", " << c.collisionData.normal.y << std::endl;

			// destroy the entity if it hits the player
			if ( false && c.first->controller > -1 || c.second->controller > -1 ) {
				auto& shape = ( c.first->controller > -1 ) ? c.second : c.first;
				// give shape lifetime in order to have it get destroyed
				shape->free( shape );
			}
			// switch velocities otherwise
			else {
				matth::vec2 p1 = c.first->transform->getPos() + mtv/2.0f;
				matth::vec2 p2 = c.second->transform->getPos() - mtv/2.0f;
				c.first->transform->setPos( p1 );
				c.second->transform->setPos( p2 );
				std::swap( c.first->rigidbody->vel, c.second->rigidbody->vel );
			}
		}
	}
};