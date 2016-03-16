#pragma once
#include "System.h"
#include "Assets.h"

class RenderSystem : public System {
	bool condition( Handle<Entity> i ) {
		return i->sprite > -1 && i->transform > -1;
	}
	void update( Handle<Entity> i ) {
		matth::mat3 m = i->transform->getGlobalTransform() *
			matth::mat3::translation( i->sprite->offset ) *
			matth::mat3::scale( i->sprite->dimension ) * 
			matth::mat3::rotation( i->sprite->angle );
		Assets::instance().drawTexture( i->sprite->assetName, m );
	}
};