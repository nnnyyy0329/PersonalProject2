#pragma once
#include "IComponent.h"

/// @brief キャラクターの体力を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class HealthComponent : public IComponent<TOwner>
{
public:

	HealthComponent(float maxLife) : m_maxLife(maxLife), m_life(maxLife) {}
	virtual ~HealthComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	/// 
	/// @param owner 初期化処理を行うキャラクター
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize(TOwner& owner) override { return true; }

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ダメージを受ける関数
	///
	/// @param damage 受けるダメージ量
	void ApplyDamage(float damage)
	{
		m_life -= damage;

		// 体力が0未満にならないように
		if(m_life < 0.0f)
		{
			m_life = 0.0f;
		}
	}

	/// @brief 死亡判定関数
	///
	/// @return 死亡しているならtrue、生存しているならfalse
	bool IsDead() const { return m_life <= 0.0f; }

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 体力の取得関数
	///
	/// @return 体力
	float GetLife() const { return m_life; }

	/// @brief 最大体力の取得関数
	///
	/// @return 最大体力
	float GetMaxLife() const { return m_maxLife; }

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	float m_maxLife;	/// 最大体力
	float m_life;		/// 体力

};

