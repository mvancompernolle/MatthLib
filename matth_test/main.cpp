#include <iostream>
#include <cassert>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Factory.h"
#include "DebugDraw.h"
#include "RigidBodyDynamics.h"

int main() {
	auto& window = Window::instance();
	auto& input = Input::instance();
	auto& time = Time::instance();

	window.initialize();
	input.initialize();
	time.initialize();

	Factory::makeBall( { 40,  40 }, { 10,10 }, 400, 40 );
	Factory::makeBall( { 70,  70 }, { 40,40 }, 120, 12 );
	Factory::makeBall( { 80, 200 }, { 0,100 }, 280, 200 );

	DebugDraw debugDrawSystem;
	RigidBodyDynamics rigidBodySystem;

	while ( window.update() ) {
		input.update();
		time.update();

		debugDrawSystem.step();
		//rigidBodySystem.step();
	}

	time.terminate();
	input.terminate();
	window.terminate();
}

//matth::mat3 matrix;
//matrix.c1 = { 1.0f, 0.0f, 5.0f };
//matrix.c2 = { 2.0f, 1.0f, 6.0f };
//matrix.c3 = { 3.0f, 4.0f, 0.0f };
//std::cout << "matrix: " << std::endl << matrix << std::endl;
//std::cout << "determinant" << matrix.determinant() << std::endl;
//std::cout << "inverse: " << std::endl << matrix * matrix.inverse() << std::endl << mat3::identity() << std::endl;
//assert( (matrix.determinant() == 0.0f || matrix * matrix.inverse() == mat3::identity()));
//system( "pause" );
//return 0;


//sfw::initContext();
//sfw::setBackgroundColor( BLACK );

//unsigned smiley = sfw::loadTextureMap( "resources/smiley.png" );

//matth::Circle c1{ {100.0f, 100.0f}, 50.0f }, c2{ { 700.0f, 100.0f }, 50.0f };
//assert( matth::collisionTest( c1, c2 ).wasCollision == false && "circle test 1 failed" );
//matth::AABB box = { {0.0f, 0.0f}, {50.0f, 50.0f} };
//matth::ConvexHull hull;
//hull.verts = { {350.0f, 200.0f}, {370.0f, 250.0f}, {370.0f, 400.0f}, {200.0f, 380.0f}, {280.0f, 250.0f} };
//Ray r;
//r.dir = { 1.0f, 0.5f };
//r.len = 50.0f;
//r.pos = { 0.0f, 0.0f };
//Plane p;
//p.pos = { 0.0f, 0.0f };
//p.normal = { -0.5f, 0.5f };

//matth::Transform t1, t2;
//matth::RigidBody r1, r2;
//t1.setPos( c1.pos );
//t1.setScale( { c1.radius * 2, c1.radius * 2 } );
////t2.setPos( c2.pos );
//t2.setScale( { 1.1f, 1.1f } );

//while ( sfw::stepContext() ) {
//	t2.setPos( t2.getPos() + vec2{ 10.0f, 10.0f } *sfw::getDeltaTime() );
//	t2.setScale( vec2{ 0.5f, 0.5f } +vec2{ std::abs( std::cos( sfw::getTime() ) ),std::abs( std::cos( sfw::getTime() ) ) } / 2.0f );
//	//t1.setAngle(90 * sfw::getTime());
//	t2.setAngle( 90 * sfw::getTime() );
//	//r1.integrate( &t1, sfw::getDeltaTime() );
//	//r2.integrate( &t2, sfw::getDeltaTime() );
//	drawCircle( t2.getGlobalTransform() * c1 );
//	drawAABB( t2.getGlobalTransform() * box );
//	drawHull( t2.getGlobalTransform() * hull );
//	drawRay( t2.getGlobalTransform() * r );
//	drawPlane( t2.getGlobalTransform() * p );

//	if ( sfw::getKey( KEY_ESCAPE ) ) {
//		break;
//	}
//}

//sfw::termContext();
//return 0;