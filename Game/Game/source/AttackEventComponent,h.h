#pragma once
#include "IComponent.h"
#include "AttackData.h"

template<typename TOwner>
class AttackEventComponent : public IComponent<TOwner>
{
public:

	AttackEventComponent() = default;
	virtual ~AttackEventComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃が開始されたときに呼ばれる関数
	///
	/// @param attackData 攻撃のデータ
	void OnAttackStart(const AttackData& attackData)
	{
		
	}
	
	/// @brief 攻撃が終了したときに呼ばれる関数
	///
	/// @param attackData 攻撃のデータ
	void OnAttackActive(const AttackData& attackData)
	{

	}

	/// @brief 攻撃が終了したときに呼ばれる関数
	///
	/// @param attackData 攻撃のデータ
	void OnAttackEnd(const AttackData& attackData)
	{

	}
	
};
