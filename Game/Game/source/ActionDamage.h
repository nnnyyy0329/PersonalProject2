#pragma once
#include "ICharacterAction.h"
#include "DamageInfo.h"

class Character;	/// キャラクタークラス

/// @brief ダメージアクションクラス
class ActionDamage : public ICharacterAction
{
public:

	ActionDamage(const DamageInfo& damageInfo)
		: 
		m_damageInfo(damageInfo),
		m_knockBackVelocity(VScale(m_damageInfo.hitDirection, m_damageInfo.damageData.knockback)),
		m_timer(damageInfo.damageData.hitStunTime) {}

	virtual ~ActionDamage() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	void Execute(Character& character) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ノックバックの更新関数
	///
	/// @param character ノックバックをさせるキャラクター
	void UpdateKnockback(Character& character);
	
	/// @brief タイマーの更新関数
	///
	/// @param character タイマーを更新するキャラクター
	void UpdateTimer(Character& character);

	/// @brief ダメージアクション終了処理関数
	///
	/// @param character アクションを終了するキャラクター
	void FinishActionDamage(Character& character);

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 被弾情報
	DamageInfo m_damageInfo;

	/// ノックバックの速度べクトル
	VECTOR m_knockBackVelocity = { 0.0f, 0.0f, 0.0f };

	/// タイマー
	float m_timer = 0.0f;

};

