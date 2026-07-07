#pragma once
#include "IComponent.h"
#include "Vector/Vector3.h"

/// @brief キャラクターの回転を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class RotationComponent : public IComponent<TOwner>
{
public:

	virtual ~RotationComponent() = default;

	//=======================================================================
	// 内部関数
	//=======================================================================

	virtual Vec3::Vector3 GetRotVector() const = 0;

protected:

	//=======================================================================
	// メンバ変数
	//=======================================================================

	/// 回転ベクトル
	Vec3::Vector3 m_rotVector = { 0.0f, 0.0f, 0.0f };

};