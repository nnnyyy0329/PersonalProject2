#pragma once

/// @brief コマンドのインターフェースクラス
///
/// @tparam TOwner コマンドを実行するキャラクターの型
template<typename TOwner>
class ICommand
{
public:

	virtual ~ICommand() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief コマンドを実行する関数
	///
	/// @param owner コマンドを実行するキャラクター
	virtual void Execute(TOwner& owner) = 0;

};