#pragma once
#include "MoveComponent.h"
#include "Character.h"

/// @brief プレイヤーの移動を管理するコンポーネントクラス
class PlayerMoveComponent : public MoveComponent<Character>
{
public:

	virtual ~PlayerMoveComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	virtual void Update(Character& owner) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 移動ベクトルを取得する関数
	///
	/// @return 移動ベクトル
	virtual VECTOR GetMoveVector() const override { return m_moveVector; }

private:

	/// 移動ベクトル
	VECTOR m_moveVector = VGet(0.0f, 0.0f, 0.0f);
};

