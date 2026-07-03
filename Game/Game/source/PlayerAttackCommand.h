#pragma once
#include "ICommand.h"

class Character;	/// キャラクタークラス

/// @brief プレイヤーの攻撃コマンドクラス
class PlayerAttackCommand : public ICommand<Character>
{
public:

	virtual ~PlayerAttackCommand() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief コマンドを実行する関数
	///
	/// @param owner コマンドを実行するキャラクター
	void Execute(Character& owner) override;

};

