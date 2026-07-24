#pragma once
#include "IComponent.h"

class Character;	/// キャラクタークラス

/// @brief プレイヤーのデバッグ用コリジョンコンポーネントクラス
class PlayerDebugColComponent : public IComponent<Character>
{
public:

	PlayerDebugColComponent() = default;
	virtual ~PlayerDebugColComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	void Update(Character& owner, const GameContext& gameContext) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief プレイヤーの当たり判定をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void DrawPlayerCollision(const Character& owner);

	/// @brief プレイヤーの攻撃判定をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void DrawPlayerAttackCollision(Character& owner);

};

