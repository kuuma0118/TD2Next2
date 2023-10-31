#include "AABB.h"

bool AABB::IsCollision(const AABB& hit) {
	// x軸方向で重なっていない
	if (min.x > hit.max.x || max.x < hit.min.x) {
		return false;
	}
	// y軸方向で重なっていない
	if (min.y > hit.max.y || max.y < hit.min.y) {
		return false;
	}
	// z軸方向で重なっていない
	if (min.z > hit.max.z || max.z < hit.min.z) {
		return false;
	}
	// すべての軸方向で重なっている
	return true;
}