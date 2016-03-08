#include "Transform.h"

Transform::Transform() : parent( nullptr ), angle( 0.0f ), pos{ 0.0f, 0.0f }, scale{ 1.0f, 1.0f } {

}

Transform::~Transform() {
	auto t = children;
	for ( Transform* child : t ) {
		child->setParent( parent );
	}
	setParent( nullptr );
}

matth::mat3 Transform::getGlobalTransform() const {
	const matth::mat3 model = matth::mat3::translation( pos ) * matth::mat3::scale( scale ) * matth::mat3::rotation( angle );
	if ( parent != nullptr ) {
		return parent->getGlobalTransform() * model;
	}
	return model;
}

matth::mat4 Transform::getRenderTransform() const {
	return matth::mat4::mat3ToMat4( getGlobalTransform() );
}

void Transform::setParent( Transform * p ) {
	if ( parent != nullptr ) parent->children.remove( this );
	if ( p != nullptr )	p->children.push_back( this );
	parent = p;
}

void Transform::setPos( const matth::vec2& position ) {
	pos = position;
}

void Transform::setScale( const matth::vec2& s ) {
	scale = s;
}

void Transform::setAngle( float deg ) {
	angle = deg;
}

matth::vec2 Transform::getPos() const {
	return pos;
}

matth::vec2 Transform::getScale() const {
	return scale;
}

float Transform::getAngle() const {
	return angle;
}


