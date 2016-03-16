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
		for each( Collision c in Collision::getData() ) {
			update( c );
		}
	}
};

class CollisionDetection : public BinarySystem {
	void onStep() { Collision::getData().clear();  }
	bool condition( Handle<Entity> i ) { return i->transform > -1 && i->collider > -1; }
	void update( Handle<Entity> i, Handle<Entity> j ) {
		auto cd = evaluateCollision( *i->transform, *i->collider, *j->transform, *j->collider );
		if ( cd.wasCollision ) {
			Collision::getData().push_back( Collision{ i, j, cd } );
		}
	}
};