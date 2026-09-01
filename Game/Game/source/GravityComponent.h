#pragma once
#include "IComponent.h"

/// @brief キャラクターの重力を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template <typename TOwner>
class GravityComponent : public IComponent<TOwner>
{
public:

	GravityComponent(float gravity = 0.25f) : m_gravity(gravity) {}
	virtual ~GravityComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================
	
	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	void Update(TOwner& owner, const GameContext& gameContext) override
	{
		// Y方向の速度に重力を加算する
		m_velocityY -= m_gravity;
	}

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 重力の強さを設定する関数
	///
	/// @param gravity 重力の強さ
	void SetGravity(float gravity) { m_gravity = gravity; }

	/// @brief Y方向の速度を設定する関数
	///
	/// @param velocityY Y方向の速度
	void SetVelocityY(float velocityY) { m_velocityY = velocityY; }

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief Y方向の速度を取得する関数
	///
	/// @return Y方向の速度
	float GetVelocityY() const { return m_velocityY; }

	/// @brief 地面のY座標を取得する関数
	///
	/// @return 地面のY座標
	float GetGroundY() const { return m_groundY; }

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 重力の強さ
	float m_gravity = 0.0f;

	/// Y方向の速度
	float m_velocityY = 0.0f;

	/// 地面のY座標
	float m_groundY = 0.0f;
};