#pragma once

/// @brief キャラクターのステートを管理するステートクラス
///
/// @tparam TOwner ステートを所有するクラスの型
template<typename TOwner>
class IState
{
public:

	virtual ~IState() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ステートに入ったときに呼ばれる関数
	///
	/// @param owner ステートに入ったキャラクター
	virtual void Enter(TOwner& owner) {};

	/// @brief ステート中の更新関数
	///
	/// @param owner ステート中の更新処理を行うキャラクター
	virtual void Update(TOwner& owner) = 0;

	/// @brief ステートから抜けるときに呼ばれる関数
	///
	/// @param owner ステートから抜けるキャラクター
	virtual void Exit(TOwner& owner) {};

};