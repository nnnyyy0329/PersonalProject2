#pragma once
#include "IComponent.h"
#include "HealthObserver.h"

/// @brief キャラクターのダメージを管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class DamageComponent : public IComponent<TOwner>, public HealthObserver<TOwner>
{
public:

	virtual ~DamageComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ダメージを受けたときに呼ばれる関数
	///
	/// @param owner ダメージを受けたキャラ
	/// @param damageInfo ダメージ情報
	virtual void OnDamaged(TOwner& owner, const DamageInfo& damageInfo) override {}

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 被弾情報を取得する関数
	///
	/// @return 被弾情報
	const DamageInfo& GetDamageInfo() const 
	{
		return m_damageInfo; 
	}

	//===========================================================================
	// セッター
	//===========================================================================

	/// @brief 被弾情報を設定する関数
	///
	/// @param damageInfo 被弾情報
	void SetDamageInfo(const DamageInfo& damageInfo)
	{
		m_damageInfo = damageInfo; 
	}

	/// @brief ヒット方向を設定する関数
	///
	/// @param direction ヒット方向
	void SetHitDirection(const Vec3::Vector3& direction)
	{
		m_damageInfo.hitDirection = direction; 
	}

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 被弾情報
	DamageInfo m_damageInfo;

};
