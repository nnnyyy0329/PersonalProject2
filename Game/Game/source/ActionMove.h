#pragma once
#include "ICharacterAction.h"

class Character;	/// キャラクタークラス

/// @brief キャラクターの移動アクションクラス
class ActionMove : public ICharacterAction
{
public:

	ActionMove() = default;
	virtual ~ActionMove() = default;

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

