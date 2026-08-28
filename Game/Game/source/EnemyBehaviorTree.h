#pragma once
#include <memory>
#include "IState.h"

class Enemy;	/// 敵クラス

/// @brief 敵をどの状態にするかを決定するクラス
class EnemyBehaviorTree
{
public:

	EnemyBehaviorTree() = default;
	~EnemyBehaviorTree() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 敵の行動を考える関数
	///
	/// @param owner 行動を考える敵
	void Think(Enemy& owner);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 敵の移動を考える関数
	///
	/// @param owner 移動を考える敵
	void ThinkMove(Enemy& owner);

	/// @brief 敵のダメージを考える関数
	///
	/// @param owner ダメージを考える敵
	void ThinkDamage(Enemy& owner);

};

