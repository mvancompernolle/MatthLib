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

	matth::CollisionData cd;
	switch ( collLeft->shape | collRight->shape ) {
	case Collider::e_CIRCLE:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->circle );
		break;
	case Collider::e_CIRCLE | Collider::e_AABB:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->aabb );
		/*if ( collLeft == &bc ) {
			cd.normal = -cd.normal;
			std::cout << "flipped" << std::endl;
		}*/
		break;
	case Collider::e_CIRCLE | Collider::e_RAY:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->ray );
		break;
	case Collider::e_CIRCLE | Collider::e_PLANE:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->plane );
		break;
	case Collider::e_CIRCLE | Collider::e_CHULL:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->circle, transRight->getGlobalTransform() * collRight->cHull );
		break;
	case Collider::e_AABB:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->aabb );
		break;
	case Collider::e_AABB | Collider::e_RAY:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->ray );
		break;
	case Collider::e_AABB | Collider::e_PLANE:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->plane );
		break;
	case Collider::e_AABB | Collider::e_CHULL:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->aabb, transRight->getGlobalTransform() * collRight->cHull );
		break;
	case Collider::e_RAY:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->ray, transRight->getGlobalTransform() * collRight->ray );
		break;
	case Collider::e_RAY | Collider::e_PLANE:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->ray, transRight->getGlobalTransform() * collRight->plane );
		break;
	case Collider::e_RAY | Collider::e_CHULL:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->ray, transRight->getGlobalTransform() * collRight->cHull );
		break;
	/*case Collider::e_PLANE:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->plane, transRight->getGlobalTransform() * collRight->plane );
		break;
	*/
	case Collider::e_PLANE | Collider::e_CHULL:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->plane, transRight->getGlobalTransform() * collRight->cHull );
		break;
	case Collider::e_CHULL:
		cd = collisionTest( transLeft->getGlobalTransform() * collLeft->cHull, transRight->getGlobalTransform() * collRight->cHull );
		break;
	default:
		cd = matth::CollisionData{ false };
	}

	return cd;
}


