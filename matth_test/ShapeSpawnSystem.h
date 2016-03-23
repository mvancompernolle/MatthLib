#pragma once

#include "System.h"
#include "Time.h"
#include "Factory.h"
#include <cstdlib>
#include <ctime>

class ShapeSpawnSystem : public System {
private:
	float getRandomPercent() const {
		return static_cast <float> ( rand() / static_cast <float> ( RAND_MAX ) );
	}
public:
	ShapeSpawnSystem() {
		std::srand( std::time( nullptr ) );
	}

	bool condition( Handle<Entity> i ) {
		return i->transform > -1 && i->shapeSpawner > -1;
	}

	Handle<Entity> createShape( Handle<Entity>& i ) const {
		auto& spawner = *i->shapeSpawner;
		const unsigned shapeType = rand() % 3;
		const float scale = spawner.minScale + getRandomPercent() * ( spawner.maxScale - spawner.minScale );
		Handle<Entity> entity;
		switch ( shapeType ) {
		case 0: {
			entity = Factory::makeDynamicCollisionShape( Collider::SHAPE::e_CIRCLE );
			entity->collider->circle.radius = 0.5f;
			break;
		}
		case 1: {
			entity = Factory::makeDynamicCollisionShape( Collider::SHAPE::e_AABB );
			entity->collider->aabb.hExtents = {0.5f, 0.5f};
			break;
		}
		case 2: {
			entity = Factory::makeDynamicCollisionShape( Collider::SHAPE::e_CHULL );
			// create an n sided polygon
			unsigned numSides = 3 +rand() % 6;
			if ( numSides == 4 ) numSides++;
			const float r = 0.5f;
			for ( unsigned i = 0; i < numSides; ++i ) {
				const float x = r * (float)cos( ( 2 * PI * i ) / numSides );
				const float y = r * (float)sin( ( 2 * PI * i ) / numSides );
				entity->collider->cHull.verts.push_back( { x, y } );
			}
			break;
		}
		case 3: {
			entity = Factory::makeDynamicCollisionShape( Collider::SHAPE::e_RAY );
			entity->collider->ray.dir = { 0.0f, 1.0f };
			entity->collider->ray.len = 1.0f;
			break;
		}
		case 4: {
			entity = Factory::makeDynamicCollisionShape( Collider::SHAPE::e_PLANE );
			entity->collider->plane.normal = { 0.0f, 1.0f };
			break;
		}
		}
		entity->transform->setScale( { scale, scale } );
		return entity;
	}

	void update( Handle<Entity> i ) {
		auto& spawner = *i->shapeSpawner;
		spawner.timeToNextSpawn -= Time::instance().getDeltaTime();
		if ( spawner.timeToNextSpawn <= 0.0f ) {
			// reset spawn time
			spawner.timeToNextSpawn = spawner.spawnMinTime + getRandomPercent() * ( spawner.spawnMaxTime - spawner.spawnMinTime );
			// spawn a new shape
			auto shape = createShape(i);

			// set life time
			shape->lifeTime = LifeTime::make();
			shape->lifeTime->setLifeTime( 20.0f );

			// get speed, angle and set vel
			const float speed = spawner.spawnMinSpeed + getRandomPercent() * ( spawner.spawnMaxSpeed - spawner.spawnMinSpeed );
			const float angle = (spawner.spawnAngle + ( getRandomPercent() - 0.5f ) * spawner.angleVariation) * DEGTORAD;
			shape->rigidbody->vel = { cos(angle) * speed, sin(angle) * speed};

			// get spin
			const float spin = spawner.minSpinSpeed + getRandomPercent() * ( spawner.maxSpinSpeed - spawner.minSpinSpeed );
			shape->rigidbody->angularVel = spin;

			// get offsets and set position
			const float xPos = i->transform->getPos().x +
				(spawner.minXOffset + getRandomPercent() * (spawner.maxXOffset - spawner.minXOffset));
			const float yPos = i->transform->getPos().y +
				( spawner.minYOffset + getRandomPercent() * ( spawner.maxYOffset - spawner.minYOffset ) );
			shape->transform->setPos( { xPos, yPos } );
		}
	}
};
