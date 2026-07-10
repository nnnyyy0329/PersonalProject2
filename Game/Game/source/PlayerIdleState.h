#pragma once
#include "IState.h"

class Player;	                /// プレイヤークラス
class PlayerAnimationComponent;	/// プレイヤーのアニメーションを管理するコンポーネントクラス

/// @brief プレイヤーのアイドル状態を管理するステートクラス
class PlayerIdleState : public IState<Player>
{
public:

	~PlayerIdleState() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ステートに入ったときに呼ばれる関数
	///
	/// @param owner ステートに入ったオーナー
	void Enter(Player& owner) override;

	/// @brief ステート中の更新関数
	///
	/// @param owner ステート中の更新処理を行うオーナー
	void Update(Player& owner) override;

	/// @brief ステートから出るときに呼ばれる関数
	///
	/// @param owner ステートから出るオーナー
	void Exit(Player& owner) override;

};

