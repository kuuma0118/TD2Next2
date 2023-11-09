#include "MoveEasing.h"

namespace MoveEasing {


	//////////////////
	///	Vector3 
	//////////////////
	namespace Vec3 {

		Vector3 EaseNomal(const Vector3 s, const Vector3 e, float t) {
			Vector3 result{};

			result.x = s.x * (1.0f - t) + t * e.x;
			result.y = s.y * (1.0f - t) + t * e.y;
			result.z = s.z * (1.0f - t) + t * e.z;

			return result;
		}

	}

}
