#pragma once
#include "IComponent.h"
#include "PlayerAttackCommand.h"

class Character;	/// キャラクタークラス

/// @brief プレイヤーの入力を管理するコンポーネントクラス
class PlayerInputComponent : public IComponent<Character>
{
public:

	virtual ~PlayerInputComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	virtual void Update(Character& owner) override;

private:
	
	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// プレイヤーの攻撃コマンド
	PlayerAttackCommand m_attackCommand;

};

