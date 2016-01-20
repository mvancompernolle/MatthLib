#pragma once
#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

namespace matth {

	struct mat3 {
		vec3 data[3];

		const vec3& operator[]( int pos ) const;
		vec3& operator[]( int pos );
		mat3 inverse() const;
		mat3 transverse() const;

		static mat3 identity();
		static mat3 zero();
		static mat3 rotation( float degrees );
		static mat3 translation( float x, float y );
		static mat3 translation( vec2 trans );
		static mat3 scale( float x, float y );
		static mat3 scale( vec2 s );
	};
};


#endif // MAT3_H
