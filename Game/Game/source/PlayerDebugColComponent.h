#pragma once
#include "IComponent.h"

class Character;	/// キャラクタークラス

/// @brief プレイヤーの当たり判定をデバッグ表示するコンポーネントクラス
class PlayerDebugColComponent : public IComponent<Character>
{
public:

	PlayerDebugColComponent() = default;
	virtual ~PlayerDebugColComponent() = default;

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
	void Update(Character& owner) override;

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

