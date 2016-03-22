#pragma once

#include "System.h"
#include "Input.h"
#include "Time.h"
#include <iostream>

class PlayerMovSystem : public System {
	bool condition( Handle<Entity> i ) {
		return i->rigidbody > -1 && i->controller > -1 && i->transform > -1;
	}

	void update( Handle<Entity> i ) {
		auto& input = Input::instance();
		auto& controller = *i->controller;
		auto& rbody = *i->rigidbody;
		auto& trans = *i->transform;
		float dt = Time::instance().getDeltaTime();

		// move left / right at constant velocity
		if ( input.getKey( controller.LEFT ) ) { rbody.vel.x = -controller.speed; }
		else if ( input.getKey( controller.RIGHT ) ) { rbody.vel.x = controller.speed; }
		else { rbody.vel.x = 0.0f; }

		// move up / down at constant velocity
		if ( input.getKey( controller.DOWN ) ) { rbody.vel.y = -controller.speed; } 
		else if ( input.getKey( controller.UP ) ) { rbody.vel.y = controller.speed; } 
		else { rbody.vel.y = 0.0f; }

		// rotate player
		if ( input.getKey( controller.CLOCKWISE ) ) { rbody.angularVel = -controller.turnSpeed;  }
		else if ( input.getKey( controller.CCLOCKWISE ) ) { rbody.angularVel = controller.turnSpeed; }
		else { rbody.angularVel = 0.0f; }

		// shrink / grow the player
		const float potentialScaleChange = controller.scaleChangeRate * dt;
		if ( input.getKey( controller.SHRINK ) && trans.getScale().x > controller.minScale ) {
			trans.setScale( { trans.getScale().x - potentialScaleChange, trans.getScale().y - potentialScaleChange } );
			if ( trans.getScale().x < controller.minScale ) {
				trans.setScale( { controller.minScale, controller.minScale } );
			}
		}
		else if ( input.getKey( controller.GROW ) && trans.getScale().x < controller.maxScale ) {
			trans.setScale( { trans.getScale().x + potentialScaleChange, trans.getScale().y + potentialScaleChange } );
			if ( trans.getScale().x > controller.maxScale ) {
				trans.setScale( { controller.maxScale, controller.maxScale } );
			}
		}

		// check to see if the user switched collision shapes
		if ( i->collider > -1 ) {
			auto& collider = *i->collider;
			if ( input.getKeyPressed(controller.CIRCLE) && collider.shape != Collider::SHAPE::e_CIRCLE) { // 1 
				collider.shape = Collider::SHAPE::e_CIRCLE;
				collider.circle.radius = 50.0f;
			}
			else if ( input.getKeyPressed( controller.AABB ) && collider.shape != Collider::SHAPE::e_AABB ) { // 2 
				collider.shape = Collider::SHAPE::e_AABB;
				collider.aabb.hExtents = { 50.0f, 50.0f };
			}
			else if ( input.getKeyPressed( controller.RAY ) && collider.shape != Collider::SHAPE::e_RAY ) { // 3
				collider.shape = Collider::SHAPE::e_RAY;
				collider.ray.dir = { 0.0f, -1.0f };
				collider.ray.len = 50.0f;
			}
			else if ( input.getKeyPressed( controller.PLANE ) && collider.shape != Collider::SHAPE::e_PLANE ) { // 4
				collider.shape = Collider::SHAPE::e_PLANE;
				collider.plane.normal = { 0.0f, -1.0f };
			}
			else if ( input.getKeyPressed( controller.CHULL ) && collider.shape != Collider::SHAPE::e_CHULL ) { // 5
				collider.shape = Collider::SHAPE::e_CHULL;
				// create an n sided polygon
				const unsigned numSides = 3 + rand() % 10;
				const float r = 50.0f;
				collider.cHull.verts.clear();
				for ( unsigned i = 0; i < numSides; ++i ) {
					const float x = r * (float)cos( ( 2 * PI * i ) / numSides );
					const float y = r * (float)sin( ( 2 * PI * i ) / numSides );
					collider.cHull.verts.push_back( { x, y } );
				}
			}
		}
	}
};