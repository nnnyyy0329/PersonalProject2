#pragma once
#include <vector>

class Character;	/// キャラクタークラス

/// @brief 当たり判定を管理するクラス
class CollisionManager
{
public:

	CollisionManager() = default;
	virtual ~CollisionManager() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 当たり判定の更新関数
	///
	/// @param characters 当たり判定を更新するキャラクターのリスト
	void Update(const std::vector<Character*>& characters);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃がヒットしたかどうかを判定する関数
	///
	/// @param attacker 攻撃を行ったキャラクター
	/// @param defender 攻撃を受けたキャラクター
	/// 
	/// @return 攻撃がヒットした場合はtrue、そうでない場合はfalse
	bool CheckHitAttack(Character* attacker, Character* defender);

	/// @brief 攻撃がヒットしたときの処理を行う関数
	///
	/// @param attacker 攻撃を行ったキャラクター
	/// @param defender 攻撃を受けたキャラクター
	void HitAttackProcess(Character* attacker, Character* defender);
};

