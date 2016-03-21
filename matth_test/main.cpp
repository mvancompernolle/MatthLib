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
#include "PlayerMovSystem.h"
#include "RenderSystem.h"
#include "ShapeSpawnSystem.h"
#include "Assets.h"
#include "matth.h"

int main() {
	auto& window = Window::instance();
	auto& input = Input::instance();
	auto& time = Time::instance();
	// create core 
	window.initialize();
	input.initialize();
	time.initialize();
	Assets::instance().loadTexture( "smiley", "../resources/smiley.png" );

	// create entities
	auto ball = Factory::makeBall( { 720,  500 }, { }, 60, 1 );
	ball->controller = PlayerController::make();
	ball->sprite = Sprite::make();
	ball->sprite->assetName = "smiley";
	ball->sprite->dimension = matth::vec2{ 72.0f, 72.0f };
	
	// make shape spawner
	Factory::makeSpawner( matth::vec2{window.getWidth() / 2.0f, 5.0f} );

	// create systems
	DebugDraw debugDrawSystem;
	RigidBodyDynamics rigidBodySystem;
	LifeTimeSystem lifeTimeSystem;
	CollisionDetection collisionSystem;
	DynamicResolution resolutionSystem;
	PlayerMovSystem movSystem;
	RenderSystem renderSystem;
	ShapeSpawnSystem spawnSystem;

	while ( window.update() ) {
		input.update();
		time.update();

		rigidBodySystem.step();
		lifeTimeSystem.step();
		collisionSystem.step();
		spawnSystem.step();
		movSystem.step();
		resolutionSystem.step();
		renderSystem.step();
		debugDrawSystem.step();

		if ( input.getKey( 256 ) ) break;
	}

	time.terminate();
	input.terminate();
	window.terminate();
}