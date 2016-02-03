#include "Transform.h"

namespace matth {
	Transform::Transform() : parent( nullptr ), angle( 0.0f ), pos{ 0.0f, 0.0f }, scale{1.0f, 1.0f} {

	}

	Transform::~Transform() {
		auto t = children;
		for ( Transform* child : t ) {
			child->setParent(parent);
		}
		setParent( nullptr );
	}

	/*void Transform::setLocalTransform( mat3& matrix ) {

	}*/

	mat3 Transform::getGlobalTransform() const {
		const mat3 model = mat3::translation( pos ) * mat3::scale( scale ) * mat3::rotation( angle );
		if ( parent != nullptr ) {
			return parent->getGlobalTransform() * model;
		}
		return model;
	}

	mat4 Transform::getRenderTransform() const {
		return mat4::mat3ToMat4( getGlobalTransform() );
	}

	void Transform::setParent( Transform * p ) {
		if ( parent != nullptr ) parent->children.remove( this );
		if( p != nullptr )	p->children.push_back( this );
		parent = p;
	}

	void Transform::setPos( const vec2& position ) {
		pos = position;
	}

	void Transform::setScale( const vec2& s ) {
		scale = s;
	}

	void Transform::setAngle( float deg ) {
		angle = deg;
	}

	vec2 Transform::getPos() const {
		return pos;
	}

	vec2 Transform::getScale() const {
		return scale;
	}

	float Transform::getAngle() const {
		return angle;
	}

}

