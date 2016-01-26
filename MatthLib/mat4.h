#pragma once
#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"
#include "mat3.h"

namespace matth {

	_declspec( align( 32 ) ) struct mat4 {

		union {
			vec4 c[4];
			float d[16];
			float d2d[4][4];
			struct {
				union { vec4 c1; vec3 right; };
				union { vec4 c2; vec3 up; };
				union { vec4 c3; vec3 forward; };
				union { vec4 c4; vec3 pos; };
			};
		};

		const vec4& operator[]( int pos ) const;
		vec4& operator[]( int pos );
		operator mat3();
		mat4 inverse() const;
		mat4 transpose() const;
		float determinant() const;

		static mat4 identity();
		static mat4 zero();
		static mat4 rotation( const vec3& rotationAxis, float degrees );
		static mat4 translation( float x, float y, float z );
		static mat4 translation( vec3 trans );
		static mat4 scale( float x, float y, float z );
		static mat4 scale( vec3 s );
	};

	mat4 operator+( const mat4& lhs, const mat4& rhs );
	mat4 operator-( const mat4& lhs, const mat4& rhs );
	mat4& operator+=( mat4& lhs, const mat4& rhs );
	mat4& operator-=( mat4& lhs, const mat4& rhs );
	mat4 operator*( const mat4& lhs, float val );
	mat4 operator*( float val, const mat4& rhs );
	mat4& operator*=( mat4& lhs, float val );
	mat4& operator*=( float val, mat4& rhs );
	mat4 operator*( const mat4& lhs, const mat4& rhs );
	mat4& operator*=( mat4& lhs, const mat4& rhs );
	vec4 operator*( const mat4& lhs, const vec4& rhs );
};


#endif // MAT4_H