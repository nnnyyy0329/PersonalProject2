#pragma once
#include "IComponent.h"
#include "AttackData.h"
#include <vector>

class Character;	/// キャラクタークラス

/// @brief プレイヤーの攻撃を管理するコンポーネントクラス
class PlayerAttackComponent : public IComponent<Character>
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

	/// @brief 攻撃データを追加する関数
	///
	/// @param attackData 追加する攻撃データ
	void AddAttackData(const AttackData& attackData) { m_attackDataList.push_back(attackData); }

	/// @brief 攻撃入力を処理する関数
	///
	/// @param owner 
	void InputAttack(Character& owner);

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

	/// 攻撃のデータのリスト
	std::vector<AttackData> m_attackDataList;

	/// 現在のコンボのインデックス
	int m_comboIndex = 0;

};

