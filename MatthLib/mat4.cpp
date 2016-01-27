#include "mat4.h"

namespace matth {

	const vec4& mat4::operator[]( int pos ) const {
		return c[pos];
	}

	vec4& mat4::operator[]( int pos ) {
		return c[pos];
	}

	mat4 mat4::inverse() const {
		return mat4();
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
		const mat3 matrix1 = {
			d2d[1][1], d2d[1][2], d2d[1][3],
			d2d[2][1], d2d[2][2], d2d[2][3],
			d2d[3][1], d2d[3][2], d2d[3][3],
		};
		const mat3 matrix2 = {
			d2d[1][0], d2d[1][2], d2d[1][3],
			d2d[2][0], d2d[2][2], d2d[2][3],
			d2d[3][0], d2d[3][2], d2d[3][3],
		};
		const mat3 matrix3 = {
			d2d[1][0], d2d[1][1], d2d[1][3],
			d2d[2][0], d2d[2][1], d2d[2][3],
			d2d[3][0], d2d[3][1], d2d[3][3],
		};
		const mat3 matrix4 = {
			d2d[1][0], d2d[1][1], d2d[1][2],
			d2d[2][0], d2d[2][1], d2d[2][2],
			d2d[3][0], d2d[3][1], d2d[3][2],
		};
		return ( d2d[0][0] * matrix1.determinant() ) - ( d2d[0][1] * matrix2.determinant() )
			+ ( d2d[0][2] * matrix3.determinant() ) - ( d2d[0][3] * matrix4.determinant() );
	}

	mat4::operator mat3() {
		return{ d2d[0][0], d2d[0][1], d2d[0][2],
			d2d[1][0], d2d[1][1], d2d[1][2],
			d2d[2][0], d2d[2][1], d2d[2][2] };
	}

	mat4 mat4::identity() {
		return{ 1.0f, 0.0f, 0.0f, 0.0f,
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

	mat4 mat4::rotation( const vec3& axis, float degrees ) {
		const float x2 = axis.x * axis.x, y2 = axis.y * axis.y, z2 = axis.z * axis.z;
		const float L = x2 + y2 + z2;
		const float rads = degrees * ( PI / 180.0f );
		mat4 matrix = identity();

		matrix[0][0] = ( x2 + ( y2 + z2 ) * cos( rads ) ) / L;
		matrix[0][1] = ( axis.x * axis.y * ( 1 - cos( rads ) ) - axis.z * sqrt( L ) * sin( rads ) ) / L;
		matrix[0][2] = ( axis.x * axis.z * ( 1 - cos( rads ) ) - axis.y * sqrt( L ) * sin( rads ) ) / L;

		matrix[0][0] = ( axis.x * axis.y * ( 1 - cos( rads ) ) + axis.z * sqrt( L ) * sin( rads ) ) / L;
		matrix[0][1] = ( y2 + ( x2 + z2 ) * cos( rads ) ) / L;
		matrix[0][2] = ( axis.x * axis.y * ( 1 - cos( rads ) ) + axis.z * sqrt( L ) * sin( rads ) ) / L;

		matrix[0][0] = ( axis.x * axis.z * ( 1 - cos( rads ) ) + axis.y * sqrt( L ) * sin( rads ) ) / L;
		matrix[0][1] = ( axis.y * axis.z * ( 1 - cos( rads ) ) + axis.x * sqrt( L ) * sin( rads ) ) / L;
		matrix[0][2] = ( z2 + ( x2 + y2 ) * cos( rads ) ) / L;

		return matrix;
	}

	mat4 mat4::translation( float x, float y, float z ) {
		return{
			1.0f,	0.0f,	0.0f,	x,
			0.0f,	1.0f,	0.0f,	y,
			0.0f,	0.0f,	1.0f,	z,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	mat4 mat4::translation( const vec3& trans ) {
		return translation( trans.x, trans.y, trans.z );
	}

	mat4 mat4::scale( float x, float y, float z ) {
		return{
			x,		0.0f,	0.0f,	0.0f,
			0.0f,	y,		0.0f,	0.0f,
			0.0f,	0.0f,	z,		0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	mat4 mat4::scale( const vec3& s ) {
		return scale( s.x, s.y, s.z );
	}

	mat4 mat4::ortho( float l, float r, float b, float t, float n, float f ) {
		return{
			2.0f / ( r - l ),	0.0f,				0.0f,				-( r + l ) / ( r - l ),
			0.0f,				2.0f / ( t - b ),	0.0f,				-( t + b ) / ( t - b ),
			0.0f,				0.0f,				-2.0f / ( f - n ),	-( f + n ) / ( f - n ),
			0.0f,				0.0f,				0.0f,				1.0f
		};
	}

	mat4 operator+( const mat4& lhs, const mat4& rhs ) {
		return mat4( lhs ) += rhs;
	}

	mat4 operator-( const mat4& lhs, const mat4& rhs ) {
		return mat4( lhs ) -= rhs;
	}

	mat4& operator+=( mat4& lhs, const mat4& rhs ) {
		for ( int i = 0; i < 4; ++i ) {
			for ( int j = 0; j < 4; ++j ) {
				lhs[i][j] += rhs[i][j];
			}
		}
		return lhs;
	}

	mat4& operator-=( mat4& lhs, const mat4& rhs ) {
		for ( int i = 0; i < 4; ++i ) {
			for ( int j = 0; j < 4; ++j ) {
				lhs[i][j] -= rhs[i][j];
			}
		}
		return lhs;
	}

	mat4 operator*( const mat4& lhs, float val ) {
		return mat4( lhs ) *= val;
	}

	mat4 operator*( float val, const mat4& rhs ) {
		return mat4( rhs ) *= val;
	}

	mat4& operator*=( mat4& lhs, float val ) {
		for ( int i = 0; i < 4; ++i ) {
			for ( int j = 0; j < 4; ++j ) {
				lhs[i][j] *= val;
			}
		}
		return lhs;
	}

	mat4& operator*=( float val, mat4& rhs ) {
		return rhs *= val;
	}

	mat4 operator*( const mat4& lhs, const mat4& rhs ) {
		return mat4( lhs ) *= rhs;
	}

	mat4& operator*=( mat4& lhs, const mat4& rhs ) {
		mat4 trans = lhs.transpose();
		lhs = { dot( trans[0], rhs[0] ),
				dot( trans[0], rhs[1] ),
				dot( trans[0], rhs[2] ),
				dot( trans[0], rhs[3] ),

				dot( trans[1], rhs[0] ),
				dot( trans[1], rhs[1] ),
				dot( trans[1], rhs[2] ),
				dot( trans[1], rhs[3] ),

				dot( trans[2], rhs[0] ),
				dot( trans[2], rhs[1] ),
				dot( trans[2], rhs[2] ),
				dot( trans[2], rhs[3] ),

				dot( trans[3], rhs[0] ),
				dot( trans[3], rhs[1] ),
				dot( trans[3], rhs[2] ),
				dot( trans[3], rhs[3] ) };
		return lhs;
	}

	vec4 operator*( const mat4& lhs, const vec4& rhs ) {
		mat4 trans = lhs.transpose();
		return{ dot( trans[0], rhs ), dot( trans[1], rhs ), dot( trans[2], rhs ), dot( trans[3], rhs ) };
	}

};
