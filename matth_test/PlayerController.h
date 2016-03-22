#pragma once

#include "GCData.h"
#include <cassert>
class PlayerController : public GCData<PlayerController> {
public:
	unsigned LEFT, RIGHT, UP, DOWN, CLOCKWISE, CCLOCKWISE, SHRINK, GROW;
	unsigned CIRCLE, AABB, RAY, PLANE, CHULL;
	float speed;
	float turnSpeed;
	float maxScale, minScale, scaleChangeRate;

	PlayerController() : LEFT( 263 ), RIGHT( 262 ), UP(265), DOWN(264), SHRINK('S'), GROW('W'),
		CLOCKWISE('D'), CCLOCKWISE('A'), CIRCLE(49), AABB( 50 ), RAY( 51 ),
		PLANE( 52 ), CHULL( 53 ), speed( 300.0f ), turnSpeed( 90.0f ),
		maxScale(3.0f), minScale(0.25f), scaleChangeRate(1.0f) {
	}

};