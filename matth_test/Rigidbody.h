#pragma once
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "vec2.h"
#include "Transform.h"
#include "GCData.h"


class RigidBody : public GCData<RigidBody>{
public:
	matth::vec2 vel, acc, force;
	float mass, drag, angularVel, angularAcc, angularDrag, torque;

	RigidBody();
	~RigidBody();
	void addForce( const matth::vec2& f );
	void addTorque( float t );
	void integrate( Transform *transform, float dt );
};


#endif // RIGIDBODY_H
