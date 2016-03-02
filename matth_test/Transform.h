#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat3.h"
#include "mat4.h"
#include "GCData.h"
#include <list>

class Transform : public GCData<Transform>{
public:
	Transform();
	~Transform();

	//void setLocalTransform( mat3& matrix );
	matth::mat3 getGlobalTransform() const;
	matth::mat4 getRenderTransform() const;

	void setParent( Transform * p );
	void setPos( const matth::vec2& position );
	void setScale( const matth::vec2& s );
	void setAngle( float deg );

	matth::vec2 getPos() const;
	matth::vec2 getScale() const;
	float getAngle() const;

private:
	Transform* parent;
	matth::vec2 pos, scale;
	float angle;
	std::list<Transform *> children;
};


#endif //TRANSFORM_H

