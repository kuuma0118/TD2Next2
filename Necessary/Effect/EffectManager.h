#pragma once
#pragma once
#include "IEffect.h"
#include <list>

template<class TEffect>
concept IsIEffect = std::is_base_of<IEffect, TEffect>::value;

class EffectManager {
public: // メンバ関数
	// 初期化
	// effectsをクリア
	void Initialize();
	// 更新
	// 全てのeffectsを更新する
	// 更新後にremove_ifで不要な要素を削除
	void Update();
	// 描画
	// 全てのeffectsを描画する
	void Draw();

	// 新しいエフェクトを登録する（可変テンプレート引数を使用）
	template <typename TEffect, typename... Args>
	void AddNewEffect(Args&&... args) {
		effects.push_back(new TEffect(std::forward<Args>(args)...));
	};

private: // メンバ変数
	
	// エフェクトの配列
	std::list<IEffect*> effects;
};