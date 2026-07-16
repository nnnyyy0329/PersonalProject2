#pragma once
#include "DamageComponent.h"

class Character;	/// キャラクタークラス

/// @brief 敵のダメージを管理するコンポーネントクラス
class EnemyDamageComponent : public DamageComponent<Character>
{
public:

	EnemyDamageComponent();
	virtual ~EnemyDamageComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	bool Initialize(Character& owner) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// @param damageInfo ダメージ情報
	void OnDamaged(Character& owner) override;

private:

};