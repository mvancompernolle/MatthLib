#include <iostream>
#include "vec2.h"
#include "mat4.h"
#include "sfwdraw.h"
#include "Transform.h"
#include "RigidBody.h"

int main() {

	sfw::initContext();
	sfw::setBackgroundColor( BLACK );

	unsigned smiley = sfw::loadTextureMap( "resources/smiley.png" );

	matth::Transform t1, t2;
	matth::RigidBody r1, r2;
	t1.setPos( { 400.0f, 200.0f } );
	t1.setScale( { 100.0f, 100.0f } );
	t2.setPos( { 1.0f, 0.0f } );
	t2.setScale( { 0.5f, 0.5f } );
	t2.setParent( &t1 );
	r1.addForce( { 10.0f, 0.0f } );
	r1.addTorque( 50.0f );
	r2.addTorque( -360.0f );
	while ( sfw::stepContext() ) {
		//t1.setAngle(90 * sfw::getTime());
		//t2.setAngle( 900 * sfw::getTime() );
		r1.integrate( &t1, sfw::getDeltaTime() );
		r2.integrate( &t2, sfw::getDeltaTime() );
		sfw::drawTextureMatrix( smiley, 0, WHITE, t1.getRenderTransform() );
		sfw::drawTextureMatrix( smiley, 0, WHITE, t2.getRenderTransform() );

		if ( sfw::getKey( KEY_ESCAPE ) ) {
			break;
		}
	}
	
	sfw::termContext();
	return 0;
}