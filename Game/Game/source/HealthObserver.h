#pragma once
#include "DamageInfo.h"

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
	/// @param damageInfo ダメージ情報
	virtual void OnDamaged(TOwner& owner, const DamageInfo& damageInfo) = 0;

};