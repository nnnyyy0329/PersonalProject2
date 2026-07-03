#pragma once

/// @brief ストラテジーのインターフェースクラス
///
/// @tparam TOwner ストラテジーを実行するキャラクターの型
template<typename TOwner>
class IStrategy
{
public:

	virtual ~IStrategy() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ストラテジーを実行する関数
	///
	/// @param owner ストラテジーを実行するキャラクター
	void Execute(TOwner& owner) = 0;

};