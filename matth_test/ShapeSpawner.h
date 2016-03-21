#pragma once

#include "GCData.h"
#include "matth.h"


class ShapeSpawner : public GCData<ShapeSpawner> {
public:
	float spawnMinTime, spawnMaxTime;
	float spawnMinSpeed, spawnMaxSpeed;
	float minSpinSpeed, maxSpinSpeed;
	float spawnAngle, angleVariation;
	float minXOffset, maxXOffset;
	float minYOffset, maxYOffset;
	float minScale, maxScale;
	float timeToNextSpawn;

	ShapeSpawner() : spawnMinTime(0.5f), spawnMaxTime(3.0f), spawnMinSpeed(100.0f), spawnMaxSpeed(300.0f),
	minSpinSpeed(-180.0f), maxSpinSpeed(180.0f), spawnAngle(90.0f), angleVariation(15.0f), 
	minXOffset(0.0f), maxXOffset(0.0f), minYOffset(0.0f), maxYOffset(0.0f),
	minScale(5.0f), maxScale(50.0f), timeToNextSpawn(spawnMinTime){
	}
private:
};