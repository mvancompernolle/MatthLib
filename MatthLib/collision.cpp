#include "collision.h"

#include <vector>

namespace matth {

	float pointPlanDist( const vec2& point, const Plane& plane ) {
		return dot(plane.normal, (point - plane.pos));
	}
	float RayPlaneDist( const Ray& ray, const Plane& plane ) {
		return dot( plane.normal, ray.pos - plane.pos ) / -dot(plane.normal, ray.dir);
	}

	CollisionData collisionTest( const ConvexHull& a, const ConvexHull& b ) {
		CollisionData collision = { false };
		float depth = INFINITY;
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

			if ( pDepth < depth ) {
				depth = pDepth;
				collision = { pDepth < 0.0f, axes[axis] * depth };
				if ( pDepth < 0.0f ) return collision;
			}
		}
		return collision;
	}

	CollisionData collisionTest( const ConvexHull& a, const Circle& b ) {
		CollisionData collision = { false };
		float depth = INFINITY;
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

			if ( pDepth < depth ) {
				depth = pDepth;
				collision = { pDepth < 0.0f, pDepth * axis };
				if ( pDepth < 0.0f ) return collision;
			}
		}
		return collision;
	}

	CollisionData collisionTest( const ConvexHull& a, const Ray& b ) {
		CollisionData collision = { false };
		float depth = INFINITY;
		std::vector<vec2> axes;

		for ( int i = 0; i < a.verts.size(); ++i ) {
			const vec2 vecBetween = a.verts[i] - a.verts[( i + 1 ) % a.verts.size()];
			axes.push_back( vecBetween.normal().perp() );
		}

		float tMin = 0.0f, tMax = 1.0f;

		for ( int i = 0; i < axes.size(); ++i ) {
			const float N = -dot( axes[i], b.pos - a.verts[i] );
			const float D = dot( axes[i], b.dir );

			if ( fabs( D ) < FLT_EPSILON ) {
				if ( N < 0.0f ) return collision;
			}

			const float t = N / D;

			if ( D < 0.0f ) {
				if ( t > tMin ) {
					tMin = t;
					collision.mvt = ( ( b.dir * b.len ).length() - tMin ) * axes[i];
					collision.wasCollision = true;
				}
			} 
		}

		return collision;
	}

	CollisionData collisionTest( const ConvexHull& a, const Plane& b ) {
		CollisionData collision = { false };
		float aMin = INFINITY;

		// loop over vertices
		for ( int i = 0; i < a.verts.size(); ++i ) {
			// get points distance form the plane
			const float pp = dot( b.normal, a.verts[i] - b.pos );
			// keep track of min point
			aMin = min( pp, aMin );
		}

		// if less than 0 there was an overlap
		if ( aMin <= 0.0f ) {
			collision.wasCollision = true;
			collision.mvt = b.normal * aMin;
		}

		return collision;
	}

	CollisionData collisionTest( const ConvexHull& a, const AABB& b ) {
		CollisionData collision = { false };
		float depth = INFINITY;
		std::vector<vec2> axes;
		std::vector<float> pDepths;

		for ( int i = 0; i < a.verts.size(); ++i ) {
			vec2 vecBetween = a.verts[i] - a.verts[( i + 1 ) % a.verts.size()];
			axes.push_back( vecBetween.normal().perp() );
		}
		axes.push_back( vec2( vec2{ b.min().x, b.max().y } - vec2{ b.max().x, b.max().y } ).normal().perp() );
		axes.push_back( vec2( vec2{ b.min().x, b.max().y } - vec2{ b.min().x, b.min().y } ).normal().perp() );

		for ( int axis = 0; axis < axes.size(); ++axis ) {
			float aMin = INFINITY, aMax = -INFINITY;
			float bMin = INFINITY, bMax = -INFINITY;

			for ( int i = 0; i < a.verts.size(); ++i ) {
				float projection = dot( axes[axis], a.verts[i] );
				aMin = fminf( projection, aMin );
				aMax = fmaxf( projection, aMax );
			}
			float projection = dot( axes[axis], vec2{b.min().x, b.min().y} );
			aMin = fminf( projection, aMin );
			aMax = fmaxf( projection, aMax );
			projection = dot( axes[axis], vec2{ b.max().x, b.max().y } );
			aMin = fminf( projection, aMin );
			aMax = fmaxf( projection, aMax );

			float pDepth = fminf( aMax - bMin, bMax - aMin );

			if ( pDepth < depth ) {
				depth = pDepth;
				collision = { pDepth < 0.0f, axes[axis] * depth };
				if ( pDepth < 0.0f ) return collision;
			}
		}
		return collision;
	}

	CollisionData collisionTest( const AABB& a, const AABB& b ) {
		CollisionData cData = { false };
		// get all of the different overlaps
		const float left = b.min().x - a.max().x;
		const float right = b.max().x - a.min().x;
		const float top = b.min().y - a.max().y;
		const float bottom = b.max().y - a.min().y;

		if ( left > 0.0f || right < 0.0f || top > 0.0f || bottom < 0.0f ) {
			return cData;
		}

		// there is an overlap
		cData.mvt.x = abs( left ) < right ? left : right;
		cData.mvt.y = abs( top ) < bottom ? top : bottom;
		( abs( cData.mvt.x ) < abs( cData.mvt.y ) ) ? cData.mvt.y = 0.0f : cData.mvt.x = 0.0f;
		cData.wasCollision = true;
		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Circle& b ) {
		CollisionData cData = { false };
		vec2 point = { clamp( b.pos.x, a.min().x, a.max().x ), clamp( b.pos.y, a.min().y, a.max().y ) };
		const float distSquared = pow( b.pos.x - point.x, 2 ) + pow( b.pos.y - point.y, 2 );
		const float radSquared = pow( b.radius, 2 );
		if ( distSquared <= radSquared ) {
			cData.wasCollision = true;
			// get collision normal
			vec2 normal = { 0.0f, 0.0f };
			if ( point.x == b.pos.x ) {
				if ( b.pos.y <= point.y ) {
					normal.y = -1.0f;
				} else {
					normal.y = 1.0f;
				}
			} else {
				if ( b.pos.x <= point.x ) {
					normal.x = -1.0f;
				} else {
					normal.x = 1.0f;
				}
			}
			cData.mvt = normal * ( sqrt( radSquared ) - sqrt( distSquared ) );
		}
		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Plane& b ) {
		CollisionData cData = { false };
		const float distToPlane = dot( b.normal, a.pos - b.pos );
		const float projExtents = a.hExtents.x * abs( dot( b.normal, { 1.0f, 0.0f } ) ) + a.hExtents.y * abs( dot( b.normal, { 0.0f, 1.0f } ) );
		if ( distToPlane <= projExtents ) {
			cData.wasCollision = true;
			cData.mvt = b.normal * ( projExtents - distToPlane );
		}
		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Ray& b ) {
		CollisionData cData = { false };
		const Plane slabs[4] = {
			{ a.min(),{ 0.0f, -1.0f } },
			{ a.max(),{ 0.0f, 1.0f } },
			{ a.min(),{ -1.0f, 0.0f } },
			{ a.max(),{ 1.0f, 0.0f } }
		};
		float slabMins[2];
		float slabMaxs[2];

		for ( int i = 0; i < 4; i += 2 ) {
			slabMins[i] = { INFINITY };
			slabMaxs[i] = { -INFINITY };
			float denom = -( dot( slabs[i].normal, b.dir ) );
			// check to see if Ray is parallel to slab
			if ( abs( denom ) < FLT_EPSILON ) {
				continue;
			}
			const float distToPlane1 = ( dot( slabs[i].normal, b.pos - slabs[i].pos ) ) / denom;
			const float distToPlane2 = ( dot( slabs[i + 1].normal, b.pos - slabs[i + 1].pos ) ) / denom;
			slabMins[i % 2] = matth::min( distToPlane1, distToPlane2 );
			slabMaxs[i % 2] = matth::max( distToPlane1, distToPlane2 );
		}
		// get overall min and max distances
		const float min = matth::max( slabMins[0], slabMins[1] ), max = matth::min( slabMaxs[0], slabMaxs[1] );
		// if min > 0, Ray starts outside and is entering box, otherwise it starts inside box and is exiting
		if ( min <= max && ( 0.0f <= min && min <= b.len ) ) {
			vec2 normal = {0.0f, 0.0f};
			float dist = clamp( min, 0.0f, b.len );
			if ( slabMins[1] > slabMins[0] ) {
				normal.x = -b.dir.x;
			}
			else {
				normal.y = -b.dir.y;
			}
			cData.wasCollision = true;
			cData.mvt = normal * dist;
		}
		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Circle& b ) {
		CollisionData cData = { false };
		const float distSquared = pow( a.pos.x - b.pos.x, 2 ) + pow( a.pos.y - b.pos.y, 2 );
		const float radSquared = pow( a.radius + b.radius, 2 );
		if ( distSquared <= radSquared ) {
			cData.wasCollision = true;
			cData.mvt = ( ( a.radius + b.radius ) - sqrt( distSquared ) ) * ( a.pos - b.pos ).normal();
		}
		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Plane& b ) {
		CollisionData cData = { false };
		const float distToPlane = dot( b.normal, ( a.pos - b.pos ) );
		if ( distToPlane <= a.radius || distToPlane < 0.0f ) {
			cData.wasCollision = true;
			cData.mvt = b.normal * (abs( distToPlane ) + (distToPlane < 0.0f ? a.radius : 0.0f));
		}
		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Ray& b ) {
		CollisionData cData = { false };
		const vec2 closestPoint = b.pos + b.dir * clamp( dot( ( a.pos - b.pos ), b.dir ), 0.0f, b.len );
		const vec2 distVec = closestPoint - b.pos;
		const float distSquared = pow( a.pos.x - closestPoint.x, 2 ) + pow( a.pos.y - closestPoint.y, 2 );
		const float radSquared = a.radius * a.radius;
		if ( distSquared <= radSquared ) {
			cData.wasCollision = true;
			cData.mvt = (a.radius - distVec.length()) * distVec.normal();
		}
		return cData;
	}

	CollisionData collisionTest( const Ray& a, const Plane& b ) {
		// gets the shortest vector to move out of collision with Plane
		CollisionData cData = { false };
		const float dotVal = dot( b.normal, a.dir );
		if ( -dotVal > 0.0f ) {
			const float RayPlanDistance = dot( b.normal, vec2{ a.pos - b.pos } ) / -dotVal;
			if ( 0.0f <= RayPlanDistance && RayPlanDistance <= a.len ) {
				cData.wasCollision = true;
				cData.mvt = -b.normal * ( a.len - RayPlanDistance );
			}
		}
		return cData;
	}
}