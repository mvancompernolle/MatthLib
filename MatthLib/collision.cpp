#include "collision.h"

#include <vector>

namespace matth {

	float pointPlanDist( const vec2& point, const plane& plane ) {
		return 0.0f;
	}
	float rayPlaneDist( const ray& ray, const plane& plane ) {
		return 0.0f;
	}

	CollisionData satHull( const ConvexHull& a, const ConvexHull& b ) {
		CollisionData collision = { false, INFINITY };
		std::vector<vec2> axes;
		std::vector<float> pDepths;

		for ( int i = 0; i < a.verts.size(); ++i ) {
			vec2 vecBetween = a.verts[i] - a.verts[( i + 1 ) % a.verts.size()];
			axes.push_back( vecBetween.normal().perp() );
		}
		for ( int i = 0; i < b.verts.size(); ++i ) {
			vec2 vecBetween = b.verts[i] - b.verts[( i + 1 ) % b.verts.size()];
			axes.push_back( vecBetween.normal().perp() );
		}

		for ( int axis = 0; axis < axes.size(); ++axis ) {
			float aMin = INFINITY, aMax = -INFINITY;
			float bMin = INFINITY, bMax = -INFINITY;

			for ( int i = 0; i < a.verts.size(); ++i ) {
				float projection = dot( axes[axis], a.verts[i] );
				aMin = fminf( projection, aMin );
				aMax = fmaxf( projection, aMax );
			}
			for ( int i = 0; i < b.verts.size(); ++i ) {
				float projection = dot( axes[axis], b.verts[i] );
				aMin = fminf( projection, aMin );
				aMax = fmaxf( projection, aMax );
			}

			float pDepth = fminf( aMax - bMin, bMax - aMin );

			if ( pDepth < collision.depth ) {
				collision = { pDepth < 0.0f, pDepth, axes[axis] };
				if ( pDepth < 0.0f ) return collision;
			}
		}
		return collision;
	}

	CollisionData satHullCircle( const ConvexHull& a, const circle& b ) {
		CollisionData collision = { false, INFINITY };
		std::vector<float> pDepths;

		for ( int vert = 0; vert < a.verts.size(); ++vert ) {
			vec2 vecBetween = a.verts[vert] - a.verts[( vert + 1 ) % a.verts.size()];
			vec2 axis = vecBetween.normal().perp();
			float aMin = INFINITY, aMax = -INFINITY;
			float bMin = INFINITY, bMax = -INFINITY;

			for ( int i = 0; i < a.verts.size(); ++i ) {
				float projection = dot( axis, a.verts[i] );
				aMin = fminf( projection, aMin );
				aMax = fmaxf( projection, aMax );
			}

			float cirProj = dot( axis, b.pos );
			bMin = cirProj - b.radius;
			bMax = cirProj + b.radius;

			float pDepth = fminf( aMax - bMin, bMax - aMin );

			if ( pDepth < collision.depth ) {
				collision = { pDepth < 0.0f, pDepth, axis };
				if ( pDepth < 0.0f ) return collision;
			}
		}
		return collision;
	}

	CollisionData satHullRay( const ConvexHull& a, const ray& b ) {
		return CollisionData();
	}

	CollisionData satHullPlane( const ConvexHull& a, const plane& b ) {
		return CollisionData();
	}

	CollisionData satHullAABB( const ConvexHull& a, const aabb& b ) {
		return CollisionData();
	}

	bool collTestAABB( const aabb& a, const aabb& b ) {
		return !( a.max().x < b.min().x || b.max().x < a.min().x || a.max().y < b.min().y || b.max().y < a.min().y );
	}

	bool collTestAABBCircle( const aabb& a, const circle& b ) {
		vec2 point = { clamp( b.pos.x, a.min().x, a.max().x ), clamp( b.pos.y, a.min().y, a.max().y ) };
		return pow( b.pos.x - point.x, 2 ) + pow( b.pos.y - point.y, 2 ) <= pow( b.radius, 2 );;
	}

	bool collTestAABBPlane( const aabb& a, const plane& b ) {
		return dot( b.normal, a.pos - b.pos )
			<= a.hExtents.x * abs( dot( b.normal, { 1.0f, 0.0f } ) ) + a.hExtents.y * abs( dot( b.normal, { 0.0f, 1.0f } ) );
	}

	bool collTestAABBRay( const aabb& a, const ray& b ) {
		const plane slabs[4] = {
			{ a.min(), {0.0f, -1.0f} },
			{ a.max(),{ 0.0f, 1.0f } },
			{ a.min(),{ -1.0f, 0.0f } },
			{ a.max(),{ 1.0f, 0.0f } }
		};
		vec2 slabMinMax[2];

		for ( int i = 0; i < 4; i+=2 ) {
			slabMinMax[i] = { INFINITY, -INFINITY };
			float denom = -( dot( slabs[i].normal, b.dir ) );
			// check to see if ray is parallel to slab
			if ( abs( denom ) < FLT_EPSILON ) {
				continue;
			}
			float distToPlane1 = ( dot( slabs[i].normal, b.pos - slabs[i].pos ) ) / denom;
			float distToPlane2 = ( dot( slabs[i+1].normal, b.pos - slabs[i+1].pos ) ) / denom;
			slabMinMax[i % 2].x = matth::min( distToPlane1, distToPlane2 );
			slabMinMax[i % 2].y = matth::max( distToPlane1, distToPlane2 );
		}
		// get overall min and max distances
		const float min = matth::min(slabMinMax[0].x, slabMinMax[1].x), max = matth::max( slabMinMax[0].y, slabMinMax[1].y );
		return min <= max && 0 <= min <= b.len;
	}

	bool collTestCircle( const circle& a, const circle& b ) {
		return pow( a.pos.x - b.pos.x, 2 ) + pow( a.pos.y - b.pos.y, 2 ) <= pow( a.radius + b.radius, 2 );
	}

	bool collTestCirclePlane( const circle& a, const plane& b ) {
		return dot( b.normal, ( a.pos - b.pos ) ) <= a.radius;
	}

	bool collTestCircleRay( const circle& a, const ray& b ) {
		vec2 pc = b.pos + b.dir * clamp( dot( ( a.pos - b.pos ), b.dir ), 0.0f, b.len );
		return pow( a.pos.x - pc.x, 2 ) + pow( a.pos.y - pc.y, 2 ) < a.radius;
	}

	bool collTestRayPlane( const ray& a, const plane& b ) {
		return -dot( b.normal, a.dir ) > 0;
	}

	CollisionData mtvAABB( const aabb& a, const aabb& b ) {
		return CollisionData();
	}

	CollisionData mtvAABBCircle( const aabb& a, const circle& b ) {
		return CollisionData();
	}

	CollisionData mtvAABBPlane( const aabb& a, const plane& b ) {
		return CollisionData();
	}

	CollisionData mtvAABBRay( const aabb& a, const ray& b ) {
		return CollisionData();
	}

	CollisionData mtvCircle( const circle& a, const circle& b ) {
		return CollisionData();
	}

	CollisionData mtvCirclePlane( const circle& a, const plane& b ) {
		return CollisionData();
	}

	CollisionData mtvCircleRay( const circle& a, const ray& b ) {
		return CollisionData();
	}

	CollisionData mtvRayPlane( const ray& a, const plane& b ) {
		return CollisionData();
	}
}