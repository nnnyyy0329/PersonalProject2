#pragma once
#include "IComponent.h"

class Character;										/// キャラクタークラス
template<typename TOwner>class DxLibAnimationComponent;	/// アニメーション管理コンポーネントクラス
template<typename TOwner>class MoveComponent;			/// 移動管理コンポーネントクラス


class PlayerAttackComponent;


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
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(Character& owner, const GameContext& gameContext) override;

	//=======================================================================
	// 内部関数
	//=======================================================================

	/// @brief アイドルアニメーションを再生する関数
	void PlayAnimIdle();

	/// @brief 移動アニメーションを再生する関数
	void PlayAnimMove();

	/// @brief 攻撃アニメーションを再生する関数
	///
	/// @param comboI 攻撃のコンボインデックス
	void PlayAnimAttack(int comboIndex);

private:
	
	//===========================================================================
	// 内部関数
	//===========================================================================

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

	/// プレイヤーの攻撃管理コンポーネントの参照用ポインタ
	PlayerAttackComponent* m_playerAttackComponent = nullptr;

};

