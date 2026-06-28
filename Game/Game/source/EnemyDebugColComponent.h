#pragma once
#include "IComponent.h"

class Character;	/// キャラクタークラス

/// @brief 敵のデバッグ用コリジョンコンポーネントクラス
class EnemyDebugColComponent : public IComponent<Character>
{
public:

	EnemyDebugColComponent() = default;
	virtual ~EnemyDebugColComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	void Update(Character& owner) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 敵の当たり判定をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void DrawEnemyCollision(const Character& owner);

};

