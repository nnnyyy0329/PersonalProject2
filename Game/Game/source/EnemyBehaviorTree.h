#pragma once
#include <memory>
#include "IState.h"

class Enemy;	/// 敵クラス

/// @brief 敵の行動を管理するビヘイビアツリークラス
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
	/// 
	/// @return 考えた行動のステートのスマートポインタ
	std::unique_ptr<IState<Enemy>> Think(Enemy& owner);

};

