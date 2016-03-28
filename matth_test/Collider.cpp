#include "Collider.h"
#include "Transform.h"


Collider::Collider() : shape( e_CIRCLE ), circle{ { 0.0f, 0.0f }, 1.0f } {

}


Collider::~Collider() {
}

matth::CollisionData evaluateCollision( const Transform& transLeft, const Collider& collLeft, const Transform& transRight, const Collider &collRight ) {
	// assumed that left shape <= right shape when called
	matth::CollisionData cd;
	switch ( collLeft.shape | collRight.shape ) {
	case Collider::e_CIRCLE:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.circle, transRight.getGlobalTransform() * collRight.circle );
		break;
	case Collider::e_CIRCLE | Collider::e_AABB:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.circle, transRight.getGlobalTransform() * collRight.aabb );
		break;
	case Collider::e_CIRCLE | Collider::e_RAY:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.circle, transRight.getGlobalTransform() * collRight.ray );
		break;
	case Collider::e_CIRCLE | Collider::e_PLANE:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.circle, transRight.getGlobalTransform() * collRight.plane );
		break;
	case Collider::e_CIRCLE | Collider::e_CHULL:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.circle, transRight.getGlobalTransform() * collRight.cHull );
		break;
	case Collider::e_AABB:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.aabb, transRight.getGlobalTransform() * collRight.aabb );
		break;
	case Collider::e_AABB | Collider::e_RAY:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.aabb, transRight.getGlobalTransform() * collRight.ray );
		break;
	case Collider::e_AABB | Collider::e_PLANE:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.aabb, transRight.getGlobalTransform() * collRight.plane );
		break;
	case Collider::e_AABB | Collider::e_CHULL:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.aabb, transRight.getGlobalTransform() * collRight.cHull );
		break;
	case Collider::e_RAY:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.ray, transRight.getGlobalTransform() * collRight.ray );
		break;
	case Collider::e_RAY | Collider::e_PLANE:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.ray, transRight.getGlobalTransform() * collRight.plane );
		break;
	case Collider::e_RAY | Collider::e_CHULL:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.ray, transRight.getGlobalTransform() * collRight.cHull );
		break;
	/*case Collider::e_PLANE:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.plane, transRight.getGlobalTransform() * collRight.plane );
		break;
	*/
	case Collider::e_PLANE | Collider::e_CHULL:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.plane, transRight.getGlobalTransform() * collRight.cHull );
		break;
	case Collider::e_CHULL:
		cd = collisionTest( transLeft.getGlobalTransform() * collLeft.cHull, transRight.getGlobalTransform() * collRight.cHull );
		break;
	default:
		cd = matth::CollisionData{ false };
	}

	return cd;
}


