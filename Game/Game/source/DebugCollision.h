#pragma once
#include "DxLib.h"
#include "AttackData.h"
#include "CharacterData.h"

class DebugCollision
{
public:

	DebugCollision() = default;
	virtual ~DebugCollision() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	void Render(const VECTOR& position, const AttackData& colData, const CharColData& charColData);
	
protected:



};

