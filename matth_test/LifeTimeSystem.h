#pragma once
#include "System.h"
#include "Time.h"

class LifeTimeSystem : public System {
public:
	virtual bool condition( Handle<Entity> i ) {
		return i->lifeTime > -1;
	}

	virtual void update( Handle<Entity> i ) {
		if ( i->lifeTime->shortenLife( Time::instance().getDeltaTime() ) ) {
			i->free( i );
		}
	}
};