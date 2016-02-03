#include <iostream>
#include <cassert>
#include "vec2.h"
#include "mat4.h"
#include "sfwdraw.h"
#include "Transform.h"
#include "RigidBody.h"
#include "collision.h"

using namespace matth;

void drawCircle(const circle& c) {
	sfw::drawCircle( c.pos.x, c.pos.y, c.radius);
}

void drawAABB( const aabb& box ) {
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

void drawRay( const ray& r ) {
	const vec2 endPoint = r.pos + r.dir * r.len;
	sfw::drawLine( r.pos.x, r.pos.y, endPoint.x, endPoint.y );
	const vec2 perpen = ( endPoint - r.pos ).normal().perp();
	const vec2 anchorPoint = r.pos + r.dir * r.len * 0.9f;
	std::vector<vec2> points;
	points.push_back( anchorPoint + perpen * r.len * 0.5f );
	points.push_back( anchorPoint - perpen * r.len * 0.5f );
	points.push_back( endPoint );
}

void drawPlane( const plane& p ) {

}

int main() {

	sfw::initContext();
	sfw::setBackgroundColor( BLACK );

	unsigned smiley = sfw::loadTextureMap( "resources/smiley.png" );

	matth::circle c1{ {100.0f, 100.0f}, 50.0f }, c2{ { 700.0f, 100.0f }, 50.0f };
	assert( matth::collTestCircle( c1, c2 ) == false && "circle test 1 failed" );
	matth::aabb box = { {200.0f, 200.0f}, {50.0f, 50.0f} };
	matth::ConvexHull hull;
	hull.verts = { {350.0f, 200.0f}, {370.0f, 250.0f}, {370.0f, 400.0f}, {200.0f, 380.0f}, {280.0f, 250.0f} };
	ray r;

	matth::Transform t1, t2;
	matth::RigidBody r1, r2;
	t1.setPos( c1.pos );
	t1.setScale( {c1.radius*2, c1.radius*2} );
	t2.setPos( c2.pos );
	t2.setScale( t1.getPos() );

	while ( sfw::stepContext() ) {
		//t1.setAngle(90 * sfw::getTime());
		//t2.setAngle( 900 * sfw::getTime() );
		//r1.integrate( &t1, sfw::getDeltaTime() );
		//r2.integrate( &t2, sfw::getDeltaTime() );
		drawCircle( c1 );
		drawCircle( c2 );
		drawAABB(box);
		drawHull( hull );

		if ( sfw::getKey( KEY_ESCAPE ) ) {
			break;
		}
	}
	
	sfw::termContext();
	return 0;
}