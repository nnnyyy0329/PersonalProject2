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
	virtual void Update(Character& owner) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃処理を行う関数
	///
	/// @param owner 攻撃処理を行うキャラクター
	/// 
	/// @return 攻撃が成功した場合 true、それ以外は false
	bool TryAttack(Character& owner);

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

