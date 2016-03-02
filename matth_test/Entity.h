#pragma once
#include "GCData.h"
#include "Collider.h"
#include "Transform.h"
#include "Rigidbody.h"

class Entity : public GCData<Entity> {
public:
	Handle<Transform> transform;
	Handle<RigidBody> rigidbody;
	Handle<Collider> collider;

	void onFree() {
		Transform::free( transform );
		RigidBody::free( rigidbody );
		Collider::free( collider );
	}
};


