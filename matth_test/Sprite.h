#pragma once

#include "GCData.h"
#include "matth.h"
#include <string>

class Sprite : public GCData<Sprite> {
public:
	matth::vec2 offset, dimension;
	float angle;
	std::string assetName;

	Sprite() : offset{}, dimension{ 1.0f,1.0f }, angle( 0.0f ), assetName( "" ) {

	}
};