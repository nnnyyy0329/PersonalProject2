#pragma once
#include "MoveComponent.h"

class Character;	/// キャラクタークラス

class EnemyMoveComponent : public MoveComponent<Character>
{
public:

	~EnemyMoveComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(Character& owner, const GameContext& gameContext) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 移動ベクトルを取得する関数
	///
	/// @return 移動ベクトル
	Vec3::Vector3 GetMoveVector() const override { return m_moveVector; }

};

