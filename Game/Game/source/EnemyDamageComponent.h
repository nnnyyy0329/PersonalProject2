#pragma once
#include "IComponent.h"
#include "HealthObserver.h"
#include "DamageInfo.h"

class Character;	/// キャラクタークラス

/// @brief 敵のダメージを管理するコンポーネントクラス
class EnemyDamageComponent : public IComponent<Character>, public HealthObserver<Character>
{
public:

	EnemyDamageComponent();
	virtual ~EnemyDamageComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	bool Initialize(Character& owner) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// @param newHealth 新しい体力の値
	/// @param maxHealth 最大体力の値
	void OnDamaged(Character& owner, float newHealth, float maxHealth) override;

	/// @brief 死亡時の処理関数
	///
	/// @param owner 死亡したキャラクター
	void OnDeath(Character& owner) override;

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 被弾情報
	DamageInfo m_damageInfo;

};