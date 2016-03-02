#include "RigidBody.h"



RigidBody::RigidBody() : vel{ 0.0f, 0.0f }, acc{ 0.0f, 0.0f }, mass( 1.0f ), drag( 0.0f ),
	angularAcc( 0.0f ), angularVel( 0.0f ), force{ 0.0f, 0.0f }, torque{ 0.0f }, angularDrag( 0.0f ) {
}


RigidBody::~RigidBody() {
}

void RigidBody::addForce( const matth::vec2& f ) {
	force += f;
}

void RigidBody::addTorque( float t ) {

	torque += t;
}

void RigidBody::integrate( Transform * transform, float dt ) {
	// apply velocity
	acc = force / mass;
	force = { 0.0f, 0.0f };
	vel += acc * dt;
	vel *= ( 1.0f - drag );
	transform->setPos( transform->getPos() + vel * dt );

	// apply rotation
	angularAcc = torque;
	torque = 0.0f;
	angularVel += angularAcc * dt;
	angularVel *= ( 1.0f - angularDrag );
	transform->setAngle( transform->getAngle() + angularVel * dt );
}

