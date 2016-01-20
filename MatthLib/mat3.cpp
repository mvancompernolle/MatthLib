#include "mat3.h"

namespace matth {

	const vec3& mat3::operator[]( int pos ) const {
		return data[pos];
	}

	vec3& mat3::operator[]( int pos ) {
		return data[pos];
	}

	mat3 mat3::inverse() const {

	}

	mat3 mat3::transverse() const {
		mat3 mat;
		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) {
				mat[i][j] = data[j][i];
			}
		}
		return mat;
	}

	// static functions ///////////////////////////
	mat3 identity() {
		return{	1, 0, 0,
				0, 1, 0,
				0, 0, 1};
	}

	mat3 zero() {
		return{ 0, 0, 0,
				0, 0, 0,
				0, 0, 0 };
	}

	mat3 rotation( float degrees ) {
		float rads = degrees * ( PI / 180 );
		return{
			cos(rads),	-sin(rads),		0.0f,
			sin(rads),	cos(rads),		0.0f,
			0.0f,		0.0f,			1.0f
		};
	}

	mat3 translation( float x, float y ) {
		return{
			1.0f,	0.0f,	x,
			0.0f,	1.0f,	y,
			0.0f,	0.0f,	1.0f
		};
	}

	mat3 translation( vec2 trans ) {
		translation( trans.x, trans.y );
	}

	mat3 scale( float x, float y ) {
		return{
			x,		0.0f,	0.0f,
			0.0f,	y,		0.0f,
			0.0f,	0.0f,	1.0f
		};
	}

	mat3 scale( vec2 s ) {
		scale( s.x, s.y );
	}
};
