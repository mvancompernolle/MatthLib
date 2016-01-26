#include "mat4.h"

namespace matth {

	const vec4& mat4::operator[]( int pos ) const {
		return c[pos];
	}

	vec4& mat4::operator[]( int pos ) {
		return c[pos];
	}

	mat4 mat4::inverse() const {

	}

	mat4 mat4::transpose() const {
		mat4 mat;
		for ( int i = 0; i < 4; ++i ) {
			for ( int j = 0; j < 4; ++j ) {
				mat[i][j] = d2d[j][i];
			}
		}
		return mat;
	}

	float mat4::determinant() const {

	}

	mat4::operator mat3() {
		return{ d2d[0][0], d2d[0][1], d2d[0][2],
			d2d[1][0], d2d[1][1], d2d[1][2],
			d2d[2][0], d2d[2][1], d2d[2][2] };
	}

	mat4 mat4::identity() {
		return{	1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 1.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 1.0f, };
	}

	mat4 mat4::zero() {
		return{ 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, };
	}

	mat4 mat4::rotation( const vec3& rotationAxis, float degrees ) {

	}

	mat4 mat4::translation( float x, float y, float z ) {
		return{
			1.0f,	0.0f,	0.0f,	x,
			0.0f,	1.0f,	0.0f,	y,
			0.0f,	0.0f,	1.0f,	z,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	mat4 mat4::translation( vec3 trans ) {
		translation( trans.x, trans.y, trans.z );
	}

	mat4 mat4::scale( float x, float y, float z ) {
		return{
			x,		0.0f,	0.0f,	0.0f,
			0.0f,	y,		0.0f,	0.0f,
			0.0f,	0.0f,	z,		0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	mat4 mat4::scale( vec3 s ) {
		scale(s.x, s.y, s.z);
	}

	mat4 operator+( const mat4& lhs, const mat4& rhs ) {

	}

	mat4 operator-( const mat4& lhs, const mat4& rhs ) {

	}

	mat4& operator+=( mat4& lhs, const mat4& rhs ) {

	}

	mat4& operator-=( mat4& lhs, const mat4& rhs ) {

	}

	mat4 operator*( const mat4& lhs, float val ) {

	}

	mat4 operator*( float val, const mat4& rhs ) {

	}

	mat4& operator*=( mat4& lhs, float val ) {

	}

	mat4& operator*=( float val, mat4& rhs ) {

	}

	mat4 operator*( const mat4& lhs, const mat4& rhs ) {

	}

	mat4& operator*=( mat4& lhs, const mat4& rhs ) {

	}

	vec4 operator*( const mat4& lhs, const vec4& rhs ) {

	}

};
