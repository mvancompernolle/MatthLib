#pragma once

#include "GCData.h"

class PushForce : public GCData<PushForce> {
public:
	float force;

	PushForce() : force(100.0f) {}
	~PushForce() {}
};