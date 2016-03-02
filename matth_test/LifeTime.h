#pragma once
#include "GCData.h"

class LifeTime : public GCData<LifeTime>{
public:
	LifeTime( float time );
	~LifeTime();
private:
	float timeLeft;
	float lifeTime;
};

