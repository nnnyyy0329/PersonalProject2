#pragma once
#include "Character.h"
#include "PlayerStateController.h"
#include "StateMachine.h"

/// @brief プレイヤークラス
class Player : public Character
{
public:

	Player() = default;
	virtual ~Player() = default;
	
	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize() override;

	/// @brief 終了関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Terminate() override;

	/// @brief 更新関数
	///
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(const GameContext& gameContext) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief デフォルトのアクションを作成する関数
	///
	/// @return デフォルトのアクションのポインタ
	std::unique_ptr<ICharacterAction> CreateDefaultAction() override;

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief ステートマシンの取得関数
	///
	/// @return ステートマシンの参照
	StateMachine<Player>& GetStateMachine() { return m_stateMachine; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief コンポーネントの設定関数
	void SetUpComponents();

	/// @brief アクションの設定関数
	void SetUpActions();

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// プレイヤーのステートコントローラー
	PlayerStateController m_stateController;

	/// プレイヤーのステートマシン
	StateMachine<Player> m_stateMachine;

};

