#pragma once
#include "IComponent.h"
#include "Vector/Vector3.h"

/// @brief キャラクターの移動を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class MoveComponent : public IComponent<TOwner>
{
public:

	virtual ~MoveComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 移動ベクトルを取得する純粋仮想関数
	///
	/// @return 移動ベクトル
	virtual Vec3::Vector3 GetMoveVector()const = 0;

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 移動ベクトル
	Vec3::Vector3 m_moveVector = { 0.0f, 0.0f, 0.0f };

};