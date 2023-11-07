#include "Random.h"

std::mt19937 Random::randomEngine_;

void Random::Initialize() {
	//ランダムエンジンの初期化
	std::random_device seedGenerator;
	randomEngine_ = std::mt19937(seedGenerator());
}

float Random::GetRandomFloat(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomEngine_);
}

int Random::GetRandomInt(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(randomEngine_);
}