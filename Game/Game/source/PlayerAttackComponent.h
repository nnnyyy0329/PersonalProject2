#pragma once
#include "AttackComponent.h"
#include "AttackData.h"
#include <vector>

class Character;	/// キャラクタークラス

/// @brief プレイヤーの攻撃を管理するコンポーネントクラス
class PlayerAttackComponent : public AttackComponent<Character>
{
public:

	PlayerAttackComponent();
	virtual ~PlayerAttackComponent() = default;

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

	/// @brief コンボ攻撃を自動で一部つなぐ関数
	///
	/// @param owner コンボ攻撃を行うキャラクター
	/// @param comboIndex 自動でつなげる1個前のコンボのインデックス
	void AutoCombo(Character& owner, int comboIndex);

	/// @brief 攻撃データ数が有効範囲かどうかを判定する関数
	/// 
	/// @return 有効範囲である場合 true、それ以外は false
	bool IsValidComboIndex() const;

	/// @brief コンボをリセットする関数
	void ResetCombo() { m_comboIndex = 0; }

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 現在のコンボのインデックスを取得する関数
	///
	/// @return 現在のコンボのインデックス
	int GetComboIndex() const { return m_comboIndex; }

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 現在のコンボのインデックス
	int m_comboIndex = 0;

};

