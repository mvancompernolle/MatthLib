#include <iostream>
#include <cassert>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Factory.h"
#include "DebugDraw.h"
#include "RigidBodyDynamics.h"
#include "LifeTimeSystem.h"
#include "CollisionSystem.h"
#include "DynamicResolution.h"
#include "StaticResolution.h"
#include "PlayerMovSystem.h"
#include "RenderSystem.h"
#include "ShapeSpawnSystem.h"
#include "PushSystem.h"
#include "Assets.h"
#include "matth.h"

int main() {
	auto& window = Window::instance();
	auto& input = Input::instance();
	auto& time = Time::instance();
	// create core 
	input.initialize();
	window.initialize();
	time.initialize();
	Assets::instance().loadTexture( "smiley", "../resources/smiley.png" );

	// create entities
	auto ball = Factory::makeBall( { window.getWidth() / 2.0f,  500 }, { }, 50, 1 );
	ball->controller = PlayerController::make();
	ball->sprite = Sprite::make();
	ball->sprite->assetName = "smiley";
	ball->sprite->dimension = matth::vec2{ 72.0f, 72.0f };
	
	// make shape spawner
	auto spawner = Factory::makeSpawner( matth::vec2{window.getWidth() / 2.0f, 15.0f} );
	spawner->shapeSpawner->minXOffset = -(window.getWidth() * 0.4f);
	spawner->shapeSpawner->maxXOffset = window.getWidth() * 0.4f ;

	// make static walls on the left and right
	auto leftWall = Factory::makeStaticCollisionShape( Collider::SHAPE::e_PLANE );
	leftWall->transform->setPos( { window.getWidth() * 0.1f, window.getHeight() / 2.0f } );
	leftWall->collider->plane.normal = matth::vec2{ 0.8f, -0.3f }.normal();
	auto rightWall = Factory::makeStaticCollisionShape( Collider::SHAPE::e_PLANE );
	rightWall->transform->setPos( { window.getWidth() * 0.9f, window.getHeight() / 2.0f } );
	rightWall->collider->plane.normal = matth::vec2{ -0.8f, -0.3f }.normal();
	auto bottomWall = Factory::makeStaticCollisionShape( Collider::SHAPE::e_PLANE );
	bottomWall->transform->setPos( { window.getWidth() * 0.5f, 0.0f } );
	bottomWall->collider->plane.normal = { 0.0f, 1.0f };

	// create systems
	DebugDraw debugDrawSystem;
	RigidBodyDynamics rigidBodySystem;
	LifeTimeSystem lifeTimeSystem;
	CollisionDetection collisionSystem;
	DynamicResolution dynamicResSystem;
	StaticResolution staticResSystem;
	PlayerMovSystem movSystem;
	RenderSystem renderSystem;
	ShapeSpawnSystem spawnSystem;
	PushSystem pushSystem;

	while ( window.update() ) {
		input.update();
		time.update();

		movSystem.step();
		//pushSystem.step();
		rigidBodySystem.step();
		lifeTimeSystem.step();
		spawnSystem.step();
		collisionSystem.step();
		dynamicResSystem.step();
		staticResSystem.step();
		renderSystem.step();
		debugDrawSystem.step();

		if ( input.getKey( KEY_ESCAPE ) ) break;
	}

	input.terminate();
	window.terminate();
	time.terminate();
}