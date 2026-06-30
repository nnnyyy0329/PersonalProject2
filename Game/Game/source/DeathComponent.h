#pragma once
#include "IComponent.h"

/// @brief キャラクターの死亡を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class DeathComponent : public IComponent<TOwner>
{
public:

	virtual ~DeathComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 死亡したときに呼ばれる関数
	///
	/// @param owner 死亡したキャラ
	virtual void OnDeath(TOwner& owner) {}


};

