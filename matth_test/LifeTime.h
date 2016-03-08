#pragma once
#include "GCData.h"
#include <iostream>

class LifeTime : public GCData<LifeTime>{
public:
	LifeTime() {}
	~LifeTime() {}
	void setLifeTime( float time ) { timeLeft = lifeTime = time; }
	bool shortenLife( float time ) { timeLeft -= time; return timeLeft <= 0.0f; }
	float timeLeft;
	float lifeTime;
};

