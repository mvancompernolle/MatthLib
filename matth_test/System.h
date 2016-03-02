#pragma once
#include "Entity.h"

class System {
	virtual bool condition( Handle<Entity> i ) = 0;
	virtual void update( Handle<Entity> i ) = 0;

	void update() {
		for ( unsigned i = 0; i < Entity::getData().size(); ++i ) {
			if ( Entity::at( i ).isValid() && condition( i ) ) {
				update( i );
			}
		}
	}
};