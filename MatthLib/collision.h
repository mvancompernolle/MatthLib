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

	float pointPlanDist( const vec2& point, const plane& plane );
	float rayPlaneDist( const ray& ray, const plane& plane );

	CollisionData satHull( const ConvexHull& a, const ConvexHull& b );
	CollisionData satHullCircle( const ConvexHull& a, const circle& b );
	CollisionData satHullRay( const ConvexHull& a, const ray& b );
	CollisionData satHullPlane( const ConvexHull& a, const plane& b );
	CollisionData satHullAABB( const ConvexHull& a, const aabb& b );

	bool collTestAABB( const aabb& a, const aabb& b );
	bool collTestAABBCircle( const aabb& a, const circle& b );
	bool collTestAABBPlane( const aabb& a, const plane& b );
	bool collTestAABBRay( const aabb& a, const ray& b );
	bool collTestCircle( const circle& a, const circle& b );
	bool collTestCirclePlane( const circle& a, const plane& b );
	bool collTestCircleRay( const circle& a, const ray& b );
	bool collTestRayPlane( const ray& a, const plane& b );

	CollisionData mtvAABB( const aabb& a, const aabb& b );
	CollisionData mtvAABBCircle( const aabb& a, const circle& b );
	CollisionData mtvAABBPlane( const aabb& a, const plane& b );
	CollisionData mtvAABBRay( const aabb& a, const ray& b );
	CollisionData mtvCircle( const circle& a, const circle& b );
	CollisionData mtvCirclePlane( const circle& a, const plane& b );
	CollisionData mtvCircleRay( const circle& a, const ray& b );
	CollisionData mtvRayPlane( const ray& a, const plane& b );

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