#pragma once
#include <random>

class Random {
public:
	static void Initialize();

	/// int型のランダムな値を取得
	static int GetRandomInt(int min, int max);

	/// float型のランダムな値を取得
	static float GetRandomFloat(float min, float max);

private:
	//ランダムエンジン
	static std::mt19937 randomEngine_;

};

