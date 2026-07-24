#pragma once
#include "RotationComponent.h"

class Character;			/// キャラクタークラス
class EnemyMoveComponent;	/// 敵の移動を管理するコンポーネントクラス

/// @brief 敵の回転を管理するコンポーネントクラス
class EnemyRotComponent : public RotationComponent<Character>
{
public:

	virtual ~EnemyRotComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize(Character& owner) override;

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	void Update(Character& owner, const GameContext& gameContext) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 回転ベクトルを取得する関数
	///
	/// @return 回転ベクトル
	Vec3::Vector3 GetRotVector() const override { return m_rotVector; }

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 敵の移動を管理するコンポーネントの参照用ポインタ
	EnemyMoveComponent* m_enemyMoveComponent = nullptr;

};

