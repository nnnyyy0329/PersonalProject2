#pragma once
#include "IComponent.h"
#include "AttackData.h"
#include <vector>
#include <stdexcept>

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

	/// @brief 攻撃データの数を取得する関数
	///
	/// @return 攻撃データの数
	/*const int GetAttackDataCount() const
	{
		return static_cast<int>(m_attackDataList.size());
	}*/

	/// @brief 攻撃データリストを取得する関数
	///
	/// @return 攻撃データリスト
	const std::vector<AttackData>& GetAttackDataList() const
	{
		return m_attackDataList;
	}

	//const AttackData& GetAttackData(int index) const
	//{
	//	// indexが範囲外の場合は例外を投げる
	//	if(index < 0 || index >= GetAttackDataCount())
	//	{
	//		throw std::runtime_error("攻撃データのインデックスが範囲外:" + std::to_string(index));
	//	}

	//	// indexが範囲内の場合は攻撃データを返す
	//	return m_attackDataList[index];
	//}

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
