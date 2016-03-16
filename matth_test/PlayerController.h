#pragma once

#include "GCData.h"
/*

*/

class PlayerController : public GCData<PlayerController> {
public:
	char LEFT, RIGHT, FORWARD;
	float speed;
	float turnSpeed;

	PlayerController() : LEFT( 'A' ), RIGHT( 'D' ), FORWARD( 'W' ), speed( 300.0f ), turnSpeed( 300.0f ) {}

};