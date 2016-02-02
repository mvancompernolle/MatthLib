#include <iostream>
#include "vec2.h"
#include "mat4.h"
#include "sfwdraw.h"

int main() {

	sfw::initContext();
	sfw::setBackgroundColor( BLACK );

	unsigned smiley = sfw::loadTextureMap( "resources/smiley.png" );

	matth::vec3 pos = {400.0f, 200.0f, 1.0f};
	while ( sfw::stepContext() ) {
		matth::mat3 model = matth::mat3::translation( pos.x, pos.y ) * matth::mat3::scale( 100, 100 ) * matth::mat3::rotation(90 * sfw::getTime());

		sfw::drawTextureMatrix( smiley, 0, WHITE, matth::mat4::mat3ToMat4(model) );

		if ( sfw::getKey( KEY_ESCAPE ) ) {
			break;
		}
	}
	
	sfw::termContext();
	return 0;
}