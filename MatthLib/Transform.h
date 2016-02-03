#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat3.h"
#include "mat4.h"
#include <list>

namespace matth {

	class Transform {
	public:
		Transform();
		~Transform();

		//void setLocalTransform( mat3& matrix );
		mat3 getGlobalTransform() const;
		mat4 getRenderTransform() const;

		void setParent( Transform * p);
		void setPos( const vec2& position );
		void setScale( const vec2& s );
		void setAngle( float deg );

		vec2 getPos() const;
		vec2 getScale() const;
		float getAngle() const;

	private:
		Transform* parent;
		vec2 pos, scale;
		float angle;
		std::list<Transform *> children;
	};

}


#endif //TRANSFORM_H

