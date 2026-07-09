#pragma once
#include "Character.h"
#include "EnemyBehaviorTree.h"

/// @brief 敵クラス
class Enemy : public Character
{
public:

	Enemy() = default;
	virtual ~Enemy() = default;

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
	virtual void Update() override;

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
	StateMachine<Enemy>& GetStateMachine() { return m_stateMachine; }

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

	/// 敵の行動を管理するビヘイビアツリー
	EnemyBehaviorTree m_behaviorTree;

	/// キャラクターのステートマシン
	StateMachine<Enemy> m_stateMachine;
};

