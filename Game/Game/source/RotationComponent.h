#pragma once
#include "IComponent.h"
#include "DxLib.h"

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

	virtual VECTOR GetRotVector() const = 0;

protected:

	//=======================================================================
	// メンバ変数
	//=======================================================================

	/// 回転ベクトル
	VECTOR m_rotVector = { 0, 0, 0 };

};