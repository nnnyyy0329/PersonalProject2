#pragma once
#include "AttackComponent.h"

/// 攻撃に関する定数を定義する名前空間
namespace Attack
{
	/// 攻撃のクールダウン時間
	constexpr float COOLDOWN = 30.0f;
}

class Character;	/// キャラクタークラス

/// @brief 敵の攻撃コンポーネントクラス
class EnemyAttackComponent : public AttackComponent<Character>
{
public:

	EnemyAttackComponent();
	virtual ~EnemyAttackComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(Character& owner, const GameContext& gameContext) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃処理を行う関数
	///
	/// @param owner 攻撃処理を行うキャラクター
	/// 
	/// @return 攻撃が成功した場合 true、それ以外は false
	bool TryAttack(Character& owner);

private:

	/// 攻撃のクールダウン時間
	float m_cooldown = 0.0f;

};

