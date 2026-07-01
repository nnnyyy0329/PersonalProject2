#pragma once

class Character;	/// キャラクタークラス

/// @brief キャラクターのアクションを管理するクラス
class ICharacterAction
{
public:

	virtual ~ICharacterAction() = default;

	//===========================================================================	
	// 内部関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	virtual void Update(Character& character) = 0;

	/// @brief アクションが終了しているかどうかを判定する関数
	///
	/// @return アクションが終了している場合はtrue、そうでない場合はfalse
	virtual bool IsFinished() const { return false; }
};