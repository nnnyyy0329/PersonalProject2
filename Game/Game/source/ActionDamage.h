#pragma once
#include "ICharacterAction.h"

class Character;	/// キャラクタークラス

/// @brief ダメージアクションクラス
class ActionDamage : public ICharacterAction
{
public:

	ActionDamage() = default;
	virtual ~ActionDamage() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	void Execute(Character& character) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

};

