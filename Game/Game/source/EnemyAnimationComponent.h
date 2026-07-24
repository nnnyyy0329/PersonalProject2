#pragma once
#include "IComponent.h"

class Character;										/// キャラクタークラス
template<typename TOwner>class DxLibAnimationComponent;	/// アニメーション管理コンポーネントクラス

/// @brief 敵のアニメーションを管理するコンポーネントクラス
class EnemyAnimationComponent : public IComponent<Character>
{
public:

	//===========================================================================
	// 基本関数
	//===========================================================================

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

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief アイドルアニメーションを再生する関数
	void PlayAnimIdle();

	/// @brief 移動アニメーションを再生する関数
	void PlayAnimMove();

	/// @brief ダメージアニメーションを再生する関数
	void PlayAnimDamage();

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 移動ベクトルに応じてアニメーションを切り替える関数
	///
	/// @param owner アニメーションを切り替えるキャラクター
	//void ChangeAnimByMovement(Character& owner);

	/// @brief 敵のアニメーションを登録する関数
	///
	/// @param owner アニメーションを登録するキャラクター
	void RegisterEnemyAnimations(Character& owner);

	/// @brief ダメージを受けたときのアニメーションを切り替える関数
	///
	/// @param owner アニメーションを切り替えるキャラクター
	void AnimationChangeByDamage(Character& owner);

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// アニメーション管理コンポーネントの参照用ポインタ
	DxLibAnimationComponent<Character>* m_animationComponent = nullptr;

};

