#pragma once

class Player;	/// プレイヤークラス

/// @brief プレイヤーのステートを管理するクラス
class PlayerStateController
{
public:

	~PlayerStateController() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief プレイヤーのステートを更新する関数
	///
	/// @param player 更新するプレイヤー
	void Update(Player& player);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief プレイヤーの移動ステートを切り替える関数
	///
	/// @param player ステートを切り替えるプレイヤー
	void ChangeMoveState(Player& player);

	/// @brief プレイヤーの攻撃ステートを切り替える関数
	///
	/// @param player ステートを切り替えるプレイヤー
	void ChangeAttackState(Player& player);

	/// @brief プレイヤーのダメージステートを切り替える関数
	///
	/// @param player ステートを切り替えるプレイヤー
	void ChangeDamageState(Player& player);

};

