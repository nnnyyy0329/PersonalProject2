#pragma once
#include "IComponent.h"
#include "Character.h"

template<typename TOwner>class DxLibAnimationComponent;	/// アニメーション管理コンポーネントクラス
template<typename TOwner>class MoveComponent;			/// 移動管理コンポーネントクラス

/// @brief プレイヤーのアニメーションを管理するコンポーネントクラス
class PlayerAnimationComponent : public IComponent<Character>
{
public:

	//=======================================================================
	// 基本関数
	//=======================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize(Character& owner) override;

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	virtual void Update(Character& owner) override;

	//=======================================================================
	// 内部関数
	//=======================================================================

	/// @brief 移動ベクトルに応じてアニメーションを切り替える関数
	void ChangeAnimByMovement();

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// アニメーション管理コンポーネントのポインタ
	DxLibAnimationComponent<Character>* m_animationComponent = nullptr;

	/// 移動管理コンポーネントのポインタ
	MoveComponent<Character>* m_moveComponent = nullptr;

};

