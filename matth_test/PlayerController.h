#pragma once

#include "GCData.h"
#include <cassert>
class PlayerController : public GCData<PlayerController> {
public:
	char LEFT, RIGHT, CLOCKWISE, CCLOCKWISE, SHRINK, GROW;
	float speed;
	float turnSpeed;
	float maxScale, minScale, scaleChangeRate;

	PlayerController() : LEFT( 'A' ), RIGHT( 'D' ), SHRINK('S'), GROW('W'),
		CLOCKWISE('E'), CCLOCKWISE('Q'), speed( 300.0f ), turnSpeed( 30.0f ),
		maxScale(3.0f), minScale(0.25f), scaleChangeRate(1.0f) {
	}

};