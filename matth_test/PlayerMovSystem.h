#pragma once

#include "System.h"
#include "Input.h"
#include "Time.h"

class PlayerMovSystem : public System {
	bool condition( Handle<Entity> i ) {
		return i->rigidbody > -1 && i->controller > -1 && i->transform > -1;
	}

	void update( Handle<Entity> i ) {
		auto& input = Input::instance();
		auto& controller = *i->controller;
		auto& rbody = *i->rigidbody;
		float dt = Time::instance().getDeltaTime();

		if ( input.getKey( controller.LEFT ) ) { rbody.addTorque( controller.turnSpeed * dt );  }
		if ( input.getKey( controller.RIGHT ) ) { rbody.addTorque( -controller.turnSpeed * dt ); }
		if ( input.getKey( controller.FORWARD ) ) {
			rbody.addForce( matth::vec2::fromAngle(i->transform->getAngle() + 90) * controller.speed * dt );
		}
	}
};