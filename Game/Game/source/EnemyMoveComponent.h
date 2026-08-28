#pragma once
#include "MoveComponent.h"

class Character;	/// キャラクタークラス

class EnemyMoveComponent : public MoveComponent<Character>
{
public:

	~EnemyMoveComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 指定したオブジェクトの位置に移動する関数
	///
	/// @param targetPos 移動先の位置
	void MoveToTarget(const Vec3::Vector3& targetPos);

	/// @brief 移動ベクトルを取得する関数
	///
	/// @return 移動ベクトル
	Vec3::Vector3 GetMoveVector() const override { return m_moveVector; }

};

