#pragma once
#include "Entity.h"
#include "vec2.h"
// Factory Method
// Constructor with a lot of meaningful defaults

struct Factory {

	static Handle<Entity> makeBall( matth::vec2 pos, matth::vec2 vel, float radius, float mass, float lifeTime = 0.0f ) {
		auto e = Entity::make();
		e->collider = Collider::make();
		e->rigidbody = RigidBody::make();
		e->transform = Transform::make();
		e->controller = PlayerController::make();

		e->collider->circle.radius = radius;
		e->collider->shape = Collider::e_CIRCLE;
		e->rigidbody->mass = mass;
		e->rigidbody->vel = vel;
		e->transform->setPos( pos );

		if ( lifeTime > 0.0f ) {
			e->lifeTime = LifeTime::make();
			e->lifeTime->setLifeTime( lifeTime );
		}
		return e;
	}

	static Handle<Entity> makeWall( matth::vec2 pos, matth::vec2 normal ) {
		auto e = Entity::make();
		e->collider = Collider::make();
		e->transform = Transform::make();

		e->collider->plane.normal = normal;
		e->collider->shape = Collider::e_PLANE;
		e->transform->setPos( pos );

		return e;
	}

};