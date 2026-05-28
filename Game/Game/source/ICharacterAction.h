#pragma once

class Character;	/// キャラクタークラス

/// @brief キャラクターのアクションを管理するクラス
class ICharacterAction
{
public:

	virtual ~ICharacterAction() = default;

	//===========================================================================	
	// 基本関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	virtual void Execute(Character& character) = 0;
};