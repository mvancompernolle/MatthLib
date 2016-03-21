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
		if ( input.getKey( controller.LEFT ) ) { rbody.vel = matth::vec2{-controller.speed, 0.0f}; }
		else if ( input.getKey( controller.RIGHT ) ) { rbody.vel = matth::vec2{ controller.speed, 0.0f }; }
		else { rbody.vel = { 0.0f, 0.0f }; }

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
	}
};