#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "CollisionShapes.h"
#include "collision.h"
#include "GCData.h"


class Transform;

class Collider : public GCData<Collider>{
public:
	enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8 } shape;
	union {
		matth::Circle circle;
		matth::Ray ray;
		matth::Plane plane;
		matth::AABB aabb;
	};
	matth::ConvexHull cHull;

	Collider();
	~Collider();
};

matth::CollisionData evaluateCollision( const Transform& at, const Collider& ac, const Transform& bt, const Collider &bc );

#endif // COLLIDER_H

