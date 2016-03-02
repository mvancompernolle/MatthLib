#pragma once
#include "System.h"
#include "renderutils.h"

class DebugDraw : public System {
public:
	virtual bool condition( Handle<Entity> i ) {
		return i->transform > -1;
	}

	virtual void update( Handle<Entity> i ) {
		drawTransform( *( i->transform ) );
		if ( i->collider > 0 )
			drawCollider( *( i->transform ), *( i->collider ) );
		if ( i->rigidbody > 0 )
			drawRigidBody( *( i->transform ), *( i->rigidbody ) );
	}
};

