#pragma once
#include "IStrategy.h"

template<typename TOwner>
class MoveStrategy : public IStrategy<TOwner>
{
public:

	virtual ~MoveStrategy() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	virtual VECTOR CalculateMove(TOwner& owner, const VECTOR& input) = 0;

};
