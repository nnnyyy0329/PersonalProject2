#pragma once
#include "IState.h"

class Player;					/// プレイヤークラス
class PlayerAnimationComponent;	/// プレイヤーのアニメーションコンポーネントクラス

/// @brief プレイヤーのダメージステートクラス
class PlayerDamageState : public IState<Player>
{
public:

	virtual ~PlayerDamageState() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ステートに入ったときに呼ばれる関数
	///
	/// @param owner ステートに入ったオーナー
	virtual void Enter(Player& owner) override;

	/// @brief ステート中の更新関数
	///
	/// @param owner ステート中の更新処理を行うオーナー
	virtual void Update(Player& owner) override;

	/// @brief ステートから抜けるときに呼ばれる関数
	///
	/// @param owner ステートから抜けるオーナー
	virtual void Exit(Player& owner) override;

};

