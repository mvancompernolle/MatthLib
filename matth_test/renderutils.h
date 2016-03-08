#pragma once
#include "mat4.h"
#include "CollisionShapes.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "sfwdraw.h"

void drawMatrix( const matth::mat3&, unsigned TINT = WHITE);
void drawVector( const matth::mat3&, const matth::vec2&, unsigned TINT = WHITE );
void drawHull( const matth::ConvexHull& hull );
void drawPlane( const matth::Plane& p );
void drawAABB( const matth::AABB& box );
void drawCircle( const matth::Circle& c );
void drawRay( const matth::Ray& r );

void drawTransform( const Transform& transform);
void drawRigidBody( const Transform& transfrom, const RigidBody& rbody );
void drawCollider( const Transform& transform, const Collider& collider);