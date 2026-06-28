#pragma once
#include "ICharacterAction.h"
#include "AttackData.h"

class Character;	/// キャラクタークラス

/// @brief 攻撃アクションクラス
class ActionAttack : public ICharacterAction
{
public:

	ActionAttack(const AttackData& attackData) : m_attackData(attackData) {}
	virtual ~ActionAttack() = default;

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

	/// @brief 攻撃が終了しているかどうか
	///
	/// @return 攻撃が終了している場合はtrue、そうでない場合はfalse
	bool IsFinished() const override { return m_isFinished; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃が開始されていないときの処理
	void NonePhaseProcess();

	/// @brief 攻撃のフェーズを更新する関数
	///
	/// @param character 攻撃を実行するキャラクター
	void UpdateAttackPhase(Character& character);

	/// @brief コリジョンの有効化関数
	///
	/// @param character 攻撃を実行するキャラクター
	void EnableCollision(Character& character);

	/// @brief コンボ受付時間かを更新する関数
	void UpdateComboReceive();



	/// @brief 攻撃が終了したときの処理関数
	///
	/// @param attackData 攻撃のデータ
	void OnAttackActive(const AttackData& attackData);



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

	/// 攻撃が終了しているかどうか
	bool m_isFinished = false;
};

