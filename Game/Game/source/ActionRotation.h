#pragma once
#include "ICharacterAction.h"

/// @brief キャラクターの回転アクションクラス
class ActionRotation : public ICharacterAction
{
public:

	ActionRotation() = default;
	virtual ~ActionRotation() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	virtual void Execute(Character& character) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

};

