#include <iostream>
#include <cassert>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"

#define TEST_VEC2 true

int main() {

#ifdef TEST_VEC2
	matth::vec2 v1 = { 0, 1 };

	// test accest
	assert( (v1.x == 0.0f && v1.y == 1.0f) && "X Y ACCESS FAILED" );
	assert( ( v1[0] == 0.0f && v1[1] == 1.0f ) && "X Y ACCESS FAILED" );

	// test comparisons
	matth::vec2 v2 = v1;
	assert( v1 == v2 && "EQUALS FAILED" );

#endif

	system( "pause" );

	return 0;
}