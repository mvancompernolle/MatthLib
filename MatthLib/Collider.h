#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "CollisionShapes.h"
#include "collision.h"

namespace matth {

	class Transform;

	class Collider {
	public:
		enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8} shape;
		union {
			Circle circle;
			Ray ray;
			Plane plane;
			AABB aabb;
		};
		ConvexHull cHull;

		Collider();
		~Collider();
	};

	CollisionData evaluateCollision(const Transform& at, const Collider& ac, const Collider &bc, const Transform& bt );
}

#endif // COLLIDER_H

