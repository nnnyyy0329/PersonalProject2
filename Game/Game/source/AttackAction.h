#pragma once
#include "ICharacterAction.h"
#include "AttackData.h"

class Character;	/// キャラクタークラス

/// @brief 攻撃アクションクラス
class AttackAction : public ICharacterAction
{
public:

	AttackAction(const AttackData& attackData) : m_attackData(attackData) {}
	virtual ~AttackAction() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	virtual void Execute(Character& character) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃がコンボを受付中かどうか
	///
	/// @return コンボを受付中である場合はtrue、そうでない場合はfalse
	bool IsCancelable() const { return m_isCancelable; }

	/// @brief 攻撃フェーズがNONEであるかどうか
	///
	/// @return 攻撃が無効である場合はtrue、そうでない場合はfalse
	bool IsAttackPhaseNone() const { return m_currentPhase == AttackPhase::NONE; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================



	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 攻撃のデータ
	AttackData m_attackData;

	/// 攻撃の現在のフェーズ
	AttackPhase m_currentPhase = AttackPhase::NONE;

	/// 現在のフェーズの経過時間
	float m_stateTime = 0.0f;

	/// 攻撃がキャンセル可能かどうか
	bool m_isCancelable = false;

};

