#pragma once

#include "System.h"
#include "collision.h"
#include <iostream>

struct Collision {
	Handle<Entity> first, second;
	matth::CollisionData collisionData;

	static std::vector<Collision>& getData() {
		static std::vector<Collision> data;
		return data;
	}
};

class CollisionSystem{
	virtual void onStep() {}
	virtual void update( Collision a ) = 0;
	virtual bool condition( Collision a ) = 0;
public:
	void step() {
		onStep();
		for each( Collision coll in Collision::getData() ) {
			if ( condition(coll) ) {
				update( coll );
			}
		}
	}
};

class CollisionDetection : public BinarySystem {
	void onStep() { Collision::getData().clear();  }
	bool condition( Handle<Entity> i ) { return i->transform > -1 && i->collider > -1; }
	void update( Handle<Entity> i, Handle<Entity> j ) {

		// ensure smaller shape type is first one passed in
		Handle<Entity> entLeft = i;
		Handle<Entity> entRight = j;
		if ( entLeft->collider->shape > entRight->collider->shape ) {
			std::swap( entLeft, entRight );
		}

		auto cd = evaluateCollision( *entLeft->transform, *entLeft->collider, 
			*entRight->transform, *entRight->collider );
		if ( cd.wasCollision ) {
			Collision::getData().push_back( Collision{ entLeft, entRight, cd } );
		}
	}
};