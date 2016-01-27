
#pragma once
#ifndef COLLISION_SHAPES_H
#define COLLISION_SHAPES_H

#include "vec2.h"
#include <vector>

namespace matth {

	struct ConvexHull {
		std::vector<vec2> verts;
	};

	struct ray {
		vec2 pos, dir;
		float len;
	};

	struct plane {
		vec2 pos, normal;
	};

	struct circle {
		vec2 pos;
		float radius;
	};

	struct aabb {
		vec2 pos;
		vec2 hExtents;
		vec2 min() const {
			return pos - hExtents;
		}
		vec2 max() const {
			return pos + hExtents;
		}
	};
}

#endif // COLLISION_SHAPES_H
