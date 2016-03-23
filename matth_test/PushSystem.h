#pragma once

#include "System.h"
#include "Time.h"
#include "matth.h"

class PushSystem : public System {
public:
	PushSystem() : minChangeTime(5.0f), maxChangeTime(10.0f) {
		resetTime();
		resetDir();
	}

	virtual bool condition( Handle<Entity> i ) {
		return i->push > -1 && i->transform > -1 && i->rigidbody > -1;
	}

	virtual void update( Handle<Entity> i ) {
		i->rigidbody->addForce( pushDir * i->push->force );
	}

	virtual void onStep() {
		// choose a new force direction
		currTime -= Time::instance().getDeltaTime();
		if ( currTime <= 0.0f ) {
			resetTime();
			resetDir();
		}
	}

private:
	matth::vec2 pushDir;
	float minChangeTime, maxChangeTime, currTime;
	
	void resetTime() {
		float percent = static_cast <float> ( rand() / static_cast <float> ( RAND_MAX ) );
		currTime = minChangeTime + percent * ( maxChangeTime - minChangeTime );
	}

	void resetDir() {
		float percent = static_cast <float> ( rand() / static_cast <float> ( RAND_MAX ) );
		pushDir.x = -1.0f + ( percent * 2.0f );
		percent = static_cast <float> ( rand() / static_cast <float> ( RAND_MAX ) );
		pushDir.y = -1.0f + ( percent * 2.0f );
		pushDir = pushDir.normal();
	}
};