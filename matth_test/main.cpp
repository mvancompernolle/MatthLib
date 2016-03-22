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
	input.initialize();
	window.initialize();
	time.initialize();
	Assets::instance().loadTexture( "smiley", "../resources/smiley.png" );

	// create entities
	auto ball = Factory::makeBall( { 720,  500 }, { }, 50, 1 );
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

		movSystem.step();
		rigidBodySystem.step();
		lifeTimeSystem.step();
		renderSystem.step();
		debugDrawSystem.step();
		collisionSystem.step();
		spawnSystem.step();
		resolutionSystem.step();

		if ( input.getKey( KEY_ESCAPE ) ) break;
	}

	input.terminate();
	window.terminate();
	time.terminate();
}