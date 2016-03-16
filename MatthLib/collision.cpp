#include "collision.h"

#include <vector>

namespace matth {

	float pointPlanDist( const vec2& point, const Plane& plane ) {
		return dot( plane.normal, ( point - plane.pos ) );
	}
	float RayPlaneDist( const Ray& ray, const Plane& plane ) {
		return dot( plane.normal, ray.pos - plane.pos ) / -dot( plane.normal, ray.dir );
	}

	CollisionData collisionTest( const ConvexHull& a, const ConvexHull& b ) {
		CollisionData cData;
		cData.depth = INFINITY;
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

			// if collision overlap is smaller update it
			if ( cData.depth >= 0.0f && pDepth < cData.depth ) {
				cData.depth = pDepth;
				cData.wasCollision = true;
				cData.normal = axes[axis];
			}
			// if no collision and gap is smaller update it
			else if( cData.depth < 0.0f && pDepth > cData.depth ){
				cData.depth = pDepth;
				cData.wasCollision = false;
				cData.normal = axes[axis];
			}
		}
		return cData;
	}

	CollisionData collisionTest( const ConvexHull& a, const Circle& b ) {
		CollisionData cData;
		cData.depth = INFINITY;
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

			if ( cData.depth >= 0.0f && pDepth < cData.depth ) {
				cData.depth = pDepth;
				cData.wasCollision = true;
				cData.normal = axis;
			}
			else if ( cData.depth < 0.0f && pDepth > cData.depth ) {
				cData.depth = pDepth;
				cData.wasCollision = false;
				cData.normal = axis;
			}
		}
		return cData;
	}

	CollisionData collisionTest( const ConvexHull& a, const Ray& b ) {
		CollisionData cData = { false };
		cData.depth = INFINITY;
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
				if ( N < 0.0f ) return cData;
				else continue;
			}

			const float t = N / D;

			if ( D < 0.0f ) {
				if ( tMin < t ) {
					tMin = t;
					cData.normal = axes[i];
					cData.depth = b.len - tMin;
				}
			} else {
				tMax = t;
			}
		}
		cData.wasCollision = tMin <= tMax;
		return cData;
	}

	CollisionData collisionTest( const ConvexHull& a, const Plane& b ) {
		CollisionData cData;
		cData.normal = b.normal;
		cData.depth = INFINITY;

		// loop over vertices
		for ( int i = 0; i < a.verts.size(); ++i ) {
			// get points distance form the plane
			const float pp = dot( b.normal, a.verts[i] - b.pos );
			// keep track of min point
			cData.depth = min( pp, cData.depth );
		}

		// if less than 0 there was an overlap
		cData.wasCollision = cData.depth <= 0.0f;
		return cData;
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
		axes.push_back( vec2( vec2{ b.min().x, b.max().y } -vec2{ b.max().x, b.max().y } ).normal().perp() );
		axes.push_back( vec2( vec2{ b.min().x, b.max().y } -vec2{ b.min().x, b.min().y } ).normal().perp() );

		for ( int axis = 0; axis < axes.size(); ++axis ) {
			float aMin = INFINITY, aMax = -INFINITY;
			float bMin = INFINITY, bMax = -INFINITY;

			for ( int i = 0; i < a.verts.size(); ++i ) {
				float projection = dot( axes[axis], a.verts[i] );
				aMin = fminf( projection, aMin );
				aMax = fmaxf( projection, aMax );
			}
			float projection = dot( axes[axis], vec2{ b.min().x, b.min().y } );
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
		// get all of the different overlaps
		CollisionData cData;
		const float left = b.min().x - a.max().x;
		const float right = b.max().x - a.min().x;
		const float top = b.min().y - a.max().y;
		const float bottom = b.max().y - a.min().y;

		if ( left > 0.0f || right < 0.0f || top > 0.0f || bottom < 0.0f ) {
			// there is no overlap
			const float gapX = abs( right ) < left ? right : left;
			const float gapY = abs( bottom ) < top ? bottom : top;
			if ( gapX <= gapY ) {
				cData.depth = gapX;
				cData.normal = ( gapX == left ? vec2{ -1.0f, 0.0f } : vec2{ 1.0f, 0.0f } );
			} else {
				cData.depth = gapY;
				cData.normal = ( gapY == top ? vec2{ 0.0f, 1.0f } : vec2{ 0.0f, -1.0f } );
			}
		} else {
			// there is an overlap
			const float collX = abs( left ) < right ? left : right;
			const float collY = abs( top ) < bottom ? top : bottom;
			if ( collX <= collY ) {
				cData.depth = collX;
				cData.normal = ( collX == right ? vec2{ 1.0f, 0.0f } : vec2{ -1.0f, 0.0f } );
			} else {
				cData.depth = collY;
				cData.normal = ( collX == bottom ? vec2{ 0.0f, -1.0f } : vec2{ 0.0f, 1.0f } );
			}
		}
		cData.wasCollision = cData.depth >= 0.0f;
		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Circle& b ) {
		CollisionData cData;
		vec2 point = { clamp( b.pos.x, a.min().x, a.max().x ), clamp( b.pos.y, a.min().y, a.max().y ) };
		const float dist = ( b.pos - a.pos ).length();

		// get collision normal
		vec2 normal = { 0.0f, 0.0f };
		if ( point.x == b.pos.x ) {
			cData.normal.y = ( b.pos.y <= point.y ? -1.0f : 0.0f );
		} else {
			cData.normal.x = ( b.pos.x <= point.x ? -1.0f : 0.0f );
		}
		cData.depth = b.radius - dist;
		cData.wasCollision = cData.depth >= 0.0f;

		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Plane& b ) {
		CollisionData cData;
		const float distToPlane = dot( b.normal, a.pos - b.pos );
		const float projExtents = a.hExtents.x * abs( dot( b.normal, { 1.0f, 0.0f } ) ) + a.hExtents.y * abs( dot( b.normal, { 0.0f, 1.0f } ) );
		cData.depth = projExtents - distToPlane;
		cData.normal = b.normal;
		cData.wasCollision = cData.depth >= 0.0f;
		return cData;
	}

	CollisionData collisionTest( const AABB& a, const Ray& b ) {
		CollisionData cData;

		// Min/Max along the X-Axis
		const Plane s1p1 = Plane{ a.max(), {1.0f, 0.0f} };
		const Plane s1p2 = Plane{ a.min(),{ -1.0f, 0.0f } };
		const float t11 = RayPlaneDist( b, s1p1 ); // Right
		const float t12 = RayPlaneDist( b, s1p2 ); // Left
		const float t1min = std::fminf( t11, t12 );
		const float t1max = std::fmaxf( t11, t12 );
		const vec2  n1 = ( t11 < t12 ) ? vec2{ 1.0f, 0.0f } : vec2{ -1.0f, 0.0f };

		// Min/Max along the Y-Axis
		const Plane s2p1 = Plane{ a.max(), {0.0f, 1.0f} };
		const Plane s2p2 = Plane{ a.min(), {0.0f, -1.0f} };
		const float t21 = RayPlaneDist( b, s2p1 );
		const float t22 = RayPlaneDist( b, s2p2 );
		const float t2min = std::fminf( t21, t22 );
		const float t2max = std::fmaxf( t21, t22 );
		const vec2  n2 = ( t21 < t22 ) ? vec2{ 0.0f, 1.0f } : vec2{ 0.0f, -1.0f };

		const float tmin = std::fmaxf( t2min, t1min );
		const float tmax = std::fminf( t2max, t1max );

		cData.depth = b.len - tmin;
		cData.wasCollision = cData.depth >= 0 && tmin <= tmax && tmin > 0;
		cData.normal = ( t1min > t2min ) ? n1 : n2;

		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Circle& b ) {
		CollisionData cData;
		const float dist = ( b.pos - a.pos ).length();
		cData.depth = ( a.radius + b.radius ) - dist;
		cData.wasCollision = cData.depth >= 0.0f;
		cData.normal = ( a.pos - b.pos ).normal();
		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Plane& b ) {
		CollisionData cData;
		const float distToPlane = dot( b.normal, ( a.pos - b.pos ) );
		cData.depth = a.radius - distToPlane;
		cData.wasCollision = distToPlane <= a.radius || distToPlane < 0.0f;
		cData.normal = b.normal;
		return cData;
	}

	CollisionData collisionTest( const Circle& a, const Ray& b ) {
		CollisionData cData;
		const vec2 closestPoint = b.pos + b.dir * clamp( dot( ( a.pos - b.pos ), b.dir ), 0.0f, b.len );
		const vec2 distVec = closestPoint - b.pos;
		const float dist = ( a.pos - closestPoint ).length();
		cData.wasCollision = dist <= a.radius;
		cData.depth = a.radius - dist;
		cData.normal = -b.dir;
		return cData;
	}

	CollisionData collisionTest( const Ray& a, const Plane& b ) {
		// gets the shortest vector to move out of collision with Plane
		CollisionData cData{ true };
		const float dotVal = dot( b.normal, a.dir );
		if ( dotVal <= 0.0f ) {
			cData.wasCollision = false;
		}
		else {
			const float rayPlaneDistance = dot( b.normal, vec2{ a.pos - b.pos } ) / -dotVal;
			cData.depth = a.len - rayPlaneDistance;
			cData.normal = -b.normal;
		}
		return cData;
	}
}