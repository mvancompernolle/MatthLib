#include <iostream>
#include <cassert>
#include "vec2.h"
#include "mat4.h"
#include "sfwdraw.h"
#include "Transform.h"
#include "RigidBody.h"
#include "collision.h"

using namespace matth;

void drawCircle( const Circle& c ) {
	sfw::drawCircle( c.pos.x, c.pos.y, c.radius );
}

void drawAABB( const AABB& box ) {
	sfw::drawLine( box.min().x, box.min().y, box.max().x, box.min().y );
	sfw::drawLine( box.min().x, box.min().y, box.min().x, box.max().y );
	sfw::drawLine( box.min().x, box.max().y, box.max().x, box.max().y );
	sfw::drawLine( box.max().x, box.max().y, box.max().x, box.min().y );
}

void drawHull( const ConvexHull& hull ) {
	for ( int i = 0; i < hull.verts.size(); ++i ) {
		sfw::drawLine( hull.verts[i].x, hull.verts[i].y, hull.verts[( i + 1 ) % hull.verts.size()].x, hull.verts[( i + 1 ) % hull.verts.size()].y );
	}
}

void drawRay( const Ray& r ) {
	const vec2 endPoint = r.pos + r.dir * r.len;
	const vec2 endLine = ( r.pos + r.dir * r.len * 0.8f );
	sfw::drawLine( r.pos.x, r.pos.y, endLine.x, endLine.y );
	const vec2 perpen = ( endPoint - r.pos ).normal().perp();
	const vec2 anchorPoint = r.pos + r.dir * r.len * 0.8f;
	std::vector<vec2> points;
	points.push_back( anchorPoint + perpen * r.len * 0.25f );
	points.push_back( anchorPoint - perpen * r.len * 0.25f );
	points.push_back( endPoint );
	ConvexHull dirHull = { points };
	drawHull( dirHull );
}

void drawPlane( const Plane& p ) {
	const vec2 right = p.normal.perp();
	const vec2 p1 = p.pos + right * 800.0f;
	const vec2 p2 = p.pos - right * 800.0f;
	sfw::drawLine( p1.x, p1.y, p2.x, p2.y );
	Ray r;
	r.dir = p.normal;
	r.len = 50.0f;
	r.pos = p.pos;
	drawRay( r );
}

int main() {

	sfw::initContext();
	sfw::setBackgroundColor( BLACK );

	unsigned smiley = sfw::loadTextureMap( "resources/smiley.png" );

	matth::Circle c1{ {100.0f, 100.0f}, 50.0f }, c2{ { 700.0f, 100.0f }, 50.0f };
	assert( matth::collisionTest( c1, c2 ).wasCollision == false && "circle test 1 failed" );
	matth::AABB box = { {0.0f, 0.0f}, {50.0f, 50.0f} };
	matth::ConvexHull hull;
	hull.verts = { {350.0f, 200.0f}, {370.0f, 250.0f}, {370.0f, 400.0f}, {200.0f, 380.0f}, {280.0f, 250.0f} };
	Ray r;
	r.dir = { 1.0f, 0.5f };
	r.len = 50.0f;
	r.pos = { 0.0f, 0.0f };
	Plane p;
	p.pos = { 0.0f, 0.0f };
	p.normal = { -0.5f, 0.5f };

	matth::Transform t1, t2;
	matth::RigidBody r1, r2;
	t1.setPos( c1.pos );
	t1.setScale( { c1.radius * 2, c1.radius * 2 } );
	//t2.setPos( c2.pos );
	t2.setScale( { 1.1f, 1.1f } );

	while ( sfw::stepContext() ) {
		t2.setPos( t2.getPos() + vec2{ 10.0f, 10.0f } *sfw::getDeltaTime() );
		t2.setScale( vec2{ 0.5f, 0.5f } +vec2{ std::abs( std::cos( sfw::getTime() ) ),std::abs( std::cos( sfw::getTime() ) ) } / 2.0f );
		//t1.setAngle(90 * sfw::getTime());
		t2.setAngle( 90 * sfw::getTime() );
		//r1.integrate( &t1, sfw::getDeltaTime() );
		//r2.integrate( &t2, sfw::getDeltaTime() );
		drawCircle( c1 );
		drawAABB( box );
		drawHull( hull );
		drawRay( t2.getGlobalTransform() * r );
		drawPlane( p );

		if ( sfw::getKey( KEY_ESCAPE ) ) {
			break;
		}
	}

	sfw::termContext();
	return 0;
}