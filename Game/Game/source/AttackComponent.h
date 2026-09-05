#pragma once
#include "IComponent.h"
#include "AttackData.h"
#include <vector>

/// @brief 攻撃を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class AttackComponent : public IComponent<TOwner>
{
public:

	virtual ~AttackComponent() = default;

	//=======================================================================
	// 内部関数
	//=======================================================================

	/// @brief 攻撃データを追加する関数
	///
	/// @param attackData 追加する攻撃データ
	void AddAttackData(const AttackData& attackData)
	{
		m_attackDataList.push_back(attackData);
	}

	//=======================================================================
	// ゲッター
	//=======================================================================

	/// @brief 攻撃データリストを取得する関数
	///
	/// @return 攻撃データリスト
	const std::vector<AttackData>& GetAttackDataList() const
	{
		return m_attackDataList;
	}

	//=======================================================================
	// セッター
	//=======================================================================

	/// @brief 攻撃データリストを設定する関数
	///
	/// @param attackDataList 攻撃データリスト
	void SetAttackDataList(const std::vector<AttackData>& attackDataList)
	{
		m_attackDataList = attackDataList;
	}

protected:

	//=======================================================================
	// メンバ変数
	//=======================================================================

	/// 攻撃のデータのリスト
	std::vector<AttackData> m_attackDataList;

};
