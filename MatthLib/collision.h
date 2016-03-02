#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include "CollisionShapes.h"

namespace matth {

	struct CollisionData {
		bool wasCollision;
		vec2 mvt;

		CollisionData( bool c = false, const vec2& d = { 0.0f, 0.0f } )
			: wasCollision( c ), mvt( d ) {
		}
	};

	float pointPlanDist( const vec2& point, const Plane& plane );
	float RayPlaneDist( const Ray& ray, const Plane& plane );

	CollisionData collisionTest( const ConvexHull& a, const ConvexHull& b );
	CollisionData collisionTest( const ConvexHull& a, const Circle& b );
	inline CollisionData collisionTest( const Circle& a, const ConvexHull& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const ConvexHull& a, const Ray& b );
	inline CollisionData collisionTest( const Ray& a, const ConvexHull& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const ConvexHull& a, const Plane& b );
	inline CollisionData collisionTest( const Plane& a, const ConvexHull& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const ConvexHull& a, const AABB& b );
	inline CollisionData collisionTest( const AABB& a, const ConvexHull& b ) { collisionTest( b, a ); }

	CollisionData collisionTest( const AABB& a, const AABB& b );
	CollisionData collisionTest( const AABB& a, const Circle& b );
	inline CollisionData collisionTest( const Circle& a, const AABB& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const AABB& a, const Plane& b );
	inline CollisionData collisionTest( const Plane& a, const AABB& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const AABB& a, const Ray& b );
	inline CollisionData collisionTest( const Ray& a, const AABB& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const Circle& a, const Circle& b );
	CollisionData collisionTest( const Circle& a, const Plane& b );
	inline CollisionData collisionTest( const Plane& a, const Circle& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const Circle& a, const Ray& b );
	inline CollisionData collisionTest( const Ray& a, const Circle& b ) { return collisionTest( b, a ); }
	CollisionData collisionTest( const Ray& a, const Plane& b );
	inline CollisionData collisionTest( const Plane& a, const Ray& b ) { return collisionTest( b, a ); }

	// use reflection of static resolution test
	// dynamic resolution test
	/*
	staticResolution(rigidbody, collisionData)
	dyanmicResolution(rigidbody, rigidbody, collisionData)
	m1v1f + m2v2f = m2v2i + m1v1i
	v1f - v2f = v2i - v1i or [v1f - v2f = v2i - v1i]

	m1v1f + m2v2f = m2v2i + m1v1i
	-m1v1f + m1v2f = -m1v2i + m1v1i
	+ --------------------------------
	m2v2f + m1v2f = m2v2i - m1v2i + 2(m1v1i)

	v2f(m2 + m1) = v2i(m2 - m1)  + 2(m1v1i)
	v2f = [v2i(m2 - m1)  + 2(m1v1i)]/(m2+m1)
	// v2f now known

	v1f - v2f = v2i - v1i
	v1f = v2i - v1i + v2f
	// v1f now known
	*/

	template<class T>
	T min( const T& a, const T& b ) {
		return ( a < b ? a : b );
	}
	template<class T>
	T max( const T& a, const T& b ) {
		return ( a > b ? a : b );
	}
	template<class T>
	T clamp( const T& a, const T& min, const T& max ) {
		if ( a < min ) return min;
		if ( a > max ) return max;
		return a;
	}
}


#endif // COLLISION_H