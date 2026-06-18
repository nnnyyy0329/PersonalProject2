#pragma once
#include "IComponent.h"

class Character;										/// キャラクタークラス
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

private:
	
	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 移動ベクトルに応じてアニメーションを切り替える関数
	void ChangeAnimByMovement();

	/// @brief プレイヤーのアニメーションを登録する関数
	///
	/// @param owner アニメーションを登録するキャラクター
	void RegisterPlayerAnimations(Character& owner);

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// アニメーション管理コンポーネントの参照用ポインタ
	DxLibAnimationComponent<Character>* m_animationComponent = nullptr;

	/// 移動管理コンポーネントの参照用ポインタ
	MoveComponent<Character>* m_moveComponent = nullptr;

};

