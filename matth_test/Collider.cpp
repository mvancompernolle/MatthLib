#include "Collider.h"
#include "Transform.h"


Collider::Collider() : shape( e_CIRCLE ), circle{ { 0.0f, 0.0f }, 1.0f } {

}


Collider::~Collider() {
}

matth::CollisionData evaluateCollision( const Transform& at, const Collider& ac, const Transform& bt, const Collider &bc ) {
	const Collider* collLeft = &ac;
	const Collider* collRight = &bc;
	const Transform* transLeft = &at;
	const Transform* transRight = &bt;
	if ( collLeft->shape > collRight->shape ) {
		std::swap( collLeft, collRight );
		std::swap( transLeft, transRight );
	}

	switch ( collLeft->shape | collRight->shape ) {
	case Collider::e_CIRCLE:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->circle );
	case Collider::e_CIRCLE | Collider::e_AABB:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->aabb );
	case Collider::e_CIRCLE | Collider::e_RAY:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->ray );
	case Collider::e_CIRCLE | Collider::e_PLANE:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->plane );
	case Collider::e_AABB:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->aabb );
	case Collider::e_AABB | Collider::e_RAY:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->ray );
	case Collider::e_AABB | Collider::e_PLANE:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->plane );
	case Collider::e_RAY | Collider::e_PLANE:
		return collisionTest( transLeft->getGlobalTransform() * collLeft->ray, transRight->getGlobalTransform() * collRight->plane );
	default:
		return matth::CollisionData{ false };
	}
}


