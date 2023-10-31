#pragma once
#include "../../HumimotoEngine/math/Vector3.h"

class AABB {
public:
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点

	// AABB * AABB
	bool IsCollision(const AABB& hit);
};