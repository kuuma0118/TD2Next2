#pragma once
#include <math.h>

namespace Easing {
	constexpr float Pi = 3.14159265359f;

		float EaseOutSine(float x) {
		return sinf((x * Pi) / 2.0f);
	}

		float EaseOutBounce(float x) {
			constexpr float n1 = 7.5625f;
			constexpr float d1 = 2.75f;

			if (x < 1.0f / d1) {
				return n1 * x * x;
			}
			else if (x < 2.0f / d1) {
				return n1 * (x -= 1.5f / d1) * x + 0.75f;
			}
			else if (x < 2.5f / d1) {
				return n1 * (x -= 2.25f / d1) * x + 0.9375f;
			}
			else {
				return n1 * (x -= 2.625f / d1) * x + 0.984375f;
			}
		}

		float EaseOutElastic(float x) {
			constexpr float c4 = (2.0f * Pi) / 3.0f;

			return x == 0.0f
				? 0.0f
				: x == 1.0f
				? 1.0f
				: powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
		}


}