#pragma once
#include "System.h"
#include "renderutils.h"
#include "Time.h"

class RigidBodyDynamics : public System {
public:
	virtual bool condition( Handle<Entity> i ) {
		return i->transform > -1 && i->rigidbody > -1;
	}

	virtual void update( Handle<Entity> i ) {
		i->rigidbody->integrate( &i->transform, Time::instance().getDeltaTime() );
	}
};

