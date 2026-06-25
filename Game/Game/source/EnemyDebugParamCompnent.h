#pragma once
#include "IComponent.h"

class Character;	/// キャラクタークラス

/// @brief 敵のデバッグパラメータを管理するコンポーネントクラス
class EnemyDebugParamComponent : public IComponent<Character>
{
public:

	EnemyDebugParamComponent() = default;
	virtual ~EnemyDebugParamComponent() = default;

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

	/// @brief 敵の体力をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void HealthDebugParam(Character& owner);
	
	/// @brief 敵の位置をデバッグ表示する関数
	///
	/// @param owner デバッグ表示を行うキャラクター
	void PositionDebugParam(Character& owner);

};

