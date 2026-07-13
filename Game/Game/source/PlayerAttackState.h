#pragma once
#include "IState.h"

class Player;					/// プレイヤークラス
class PlayerAttackComponent;	/// プレイヤーの攻撃を管理するコンポーネントクラス
class PlayerAnimationComponent;	/// プレイヤーのアニメーションを管理するコンポーネントクラス

/// @brief プレイヤーの攻撃状態を管理するステートクラス
class PlayerAttackState : public IState<Player>
{
public:

	~PlayerAttackState() = default;

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

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// プレイヤーの攻撃コンポーネントの参照用ポインタ
	PlayerAttackComponent* m_playerAttackComponent = nullptr;

	/// プレイヤーのアニメーションコンポーネントの参照用ポインタ
	PlayerAnimationComponent* m_playerAnimationComponent = nullptr;

};

