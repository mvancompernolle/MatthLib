#pragma once
#include "GCData.h"
#include "Collider.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "LifeTime.h"
#include "PlayerController.h"

class Entity : public GCData<Entity> {
public:
	Handle<Transform> transform;
	Handle<RigidBody> rigidbody;
	Handle<Collider> collider;
	Handle<LifeTime> lifeTime;
	Handle<PlayerController> controller;

	void onFree() {
		Transform::free( transform );
		RigidBody::free( rigidbody );
		Collider::free( collider );
		LifeTime::free( lifeTime );
		PlayerController::free( controller );
	}
};


