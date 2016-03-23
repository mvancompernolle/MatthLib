#pragma once

#include "CollisionSystem.h"
#include "matth.h"

class StaticResolution : public CollisionSystem {
	bool condition( Collision c ) {
		return c.first->rigidbody > -1 && c.second->rigidbody < 0 ||
			c.first->rigidbody < 0 && c.second->rigidbody > -1;
	}

	void update( Collision c ) {
		if ( c.collisionData.wasCollision ) {
			Handle<Entity> staticBody;
			Handle<Entity> dynamicBody;
			matth::vec2 normal = c.collisionData.normal;

			if ( c.first->rigidbody > -1 ) {
				dynamicBody = c.first;
			}
			else {
				dynamicBody = c.second;
				//normal = -normal;
			}

			std::cout << "depth: " << c.collisionData.depth 
			 << " normal: " << normal.x << ", " << normal.y << std::endl;

			// move the dynamic body by the minimum translate
			matth::vec2 mtv = c.collisionData.depth * normal;
			matth::vec2 newPos = dynamicBody->transform->getPos() + mtv;
			dynamicBody->transform->setPos( newPos );
			// reflect the velocity of the dynamic body
			dynamicBody->rigidbody->vel = dynamicBody->rigidbody->vel.reflect( c.collisionData.normal );
		}
	}
};