#pragma once
#include "IComponent.h"

class Character;	/// キャラクタークラス

/// @brief プレイヤーのデバッグパラメータを管理するコンポーネントクラス
class PlayerDebugParamComponent : public IComponent<Character>
{
public:

	PlayerDebugParamComponent() = default;
	virtual ~PlayerDebugParamComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize(Character& owner) override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief プレイヤーの体力をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void HealthDebugParam(Character& owner);

	/// @brief プレイヤーの位置をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void PositionDebugParam(Character& owner);

};

