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
	virtual void Update(Character& character) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief キャラクターを移動させる関数
	///
	/// @param character 移動させるキャラクター
	void Move(Character& character);

	/// @brief キャラクターを回転させる関数
	///
	/// @param character 回転させるキャラクター
	void Rotate(Character& character);

};

