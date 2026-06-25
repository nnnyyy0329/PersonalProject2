#pragma once

/// @brief 体力の変化や死亡を監視するオブザーバークラス
///
/// @tparam TOwner 監視対象のオーナークラス
template<typename TOwner>
class HealthObserver
{
public:

	virtual ~HealthObserver() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 体力が変化したときに呼ばれる関数
	///
	/// @param owner オーナーのポインタ
	/// @param newHealth 新しい体力の値
	/// @param maxHealth 最大体力の値
	virtual void OnDamaged(TOwner& owner, float newHealth, float maxHealth) = 0;

	/// @brief 死亡したときに呼ばれる関数
	/// 
	/// @param owner オーナーのポインタ
	virtual void OnDeath(TOwner& owner) = 0;

};