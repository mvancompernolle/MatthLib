#include "mat3.h"

namespace matth {

	const vec3& mat3::operator[]( int pos ) const {
		return c[pos];
	}

	vec3& mat3::operator[]( int pos ) {
		return c[pos];
	}

	mat3 mat3::inverse() const {
		mat3 matrix = mat3::zero();
		float det = determinant();
		if ( det != 0.0f ) {
			return ( 1.0f / determinant() ) * transpose();
		}
		return matrix;

	}

	mat3 mat3::transpose() const {
		mat3 mat;
		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) {
				mat[i][j] = d2d[j][i];
			}
		}
		return mat;
	}

	float mat3::determinant() const {
		return c[0][0] * ( c[1][1] * c[2][2] - c[1][2] * c[2][1] ) +
			c[1][0] * ( c[0][1] * c[2][2] - c[2][1] * c[0][2] ) +
			c[2][0] * ( c[0][1] * c[1][2] - c[1][1] * c[0][2] );
	}

	// static functions ///////////////////////////
	mat3 mat3::identity() {
		return{	1, 0, 0,
				0, 1, 0,
				0, 0, 1};
	}

	mat3 mat3::zero() {
		return{ 0, 0, 0,
				0, 0, 0,
				0, 0, 0 };
	}

	mat3 mat3::rotation( float degrees ) {
		float rads = degrees * ( PI / 180 );
		return{
			cos(rads),	-sin(rads),		0.0f,
			sin(rads),	cos(rads),		0.0f,
			0.0f,		0.0f,			1.0f
		};
	}

	mat3 mat3::translation( float x, float y ) {
		return{
			1.0f,	0.0f,	x,
			0.0f,	1.0f,	y,
			0.0f,	0.0f,	1.0f
		};
	}

	mat3 mat3::translation( vec2 trans ) {
		return translation( trans.x, trans.y );
	}

	mat3 mat3::scale( float x, float y ) {
		return{
			x,		0.0f,	0.0f,
			0.0f,	y,		0.0f,
			0.0f,	0.0f,	1.0f
		};
	}

	mat3 mat3::scale( vec2 s ) {
		return scale( s.x, s.y );
	}

	mat3 operator+( const mat3& lhs, const mat3& rhs ) {
		return mat3( lhs ) += rhs;
	}

	mat3 operator-( const mat3& lhs, const mat3& rhs ) {
		return mat3( lhs ) -= rhs;
	}

	mat3& operator+=( mat3& lhs, const mat3& rhs ) {
		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) {
				lhs[i][j] += rhs[i][j];
			}
		}
		return lhs;
	}

	mat3& operator-=( mat3& lhs, const mat3& rhs ) {
		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) {
				lhs[i][j] -= rhs[i][j];
			}
		}
		return lhs;
	}

	mat3 operator*( const mat3& lhs, float val ) {
		return mat3( lhs ) *= val;
	}

	mat3 operator*( float val, const mat3& rhs ) {
		return mat3( rhs ) *= val;
	}

	mat3& operator*=( mat3& lhs, float val ) {
		for ( int i = 0; i < 3; ++i ) {
			for ( int j = 0; j < 3; ++j ) {
				lhs[i][j] *= val;
			}
		}
		return lhs;
	}

	mat3& operator*=( float val, mat3& rhs ) {
		return rhs * val;
	}

	mat3 operator*( const mat3& lhs, mat3& rhs ) {
		return mat3( lhs ) *= rhs;
	}

	mat3& operator*=( mat3& lhs, const mat3& rhs ) {
		mat3 trans = lhs.transpose();
		lhs = { dot( trans[0], rhs[0] ), 
			dot( trans[0], rhs[1] ),
			dot( trans[0], rhs[2] ),

			dot( trans[1], rhs[0] ),
			dot( trans[1], rhs[1] ),
			dot( trans[1], rhs[2] ),

			dot( trans[2], rhs[0] ),
			dot( trans[2], rhs[1] ),
			dot( trans[2], rhs[2] ),
		};
		return lhs;
	}

	vec3 operator*( const mat3& lhs, const vec3& rhs ) {
		mat3 trans = lhs.transpose();
		return { dot( trans[0], rhs ), dot( trans[1], rhs ),dot( trans[2], rhs ) };
	}
};
