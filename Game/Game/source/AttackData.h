#pragma once
#include "AttackTiming.h"
#include "CollisionData.h"
#include "AttackDamageData.h"
#include "KnockbackData.h"
#include "AttackMoveData.h"
#include "EffectData.h"
#include "SoundData.h"
#include "CameraShakeData.h"

/// @brief 攻撃データ構造体
struct AttackData
{
	AttackTiming timing;				/// 攻撃のタイミングデータ
	CollisionData colData;				/// 当たり判定のデータ
	AttackDamageData damageData;		/// 攻撃ダメージのデータ
	KnockbackData knockbackData;		/// ノックバックデータ
	AttackMoveData moveData;			/// 攻撃移動のデータ
	EffectData effectData;				/// エフェクトのデータ
	SoundData soundData;				/// サウンドのデータ
	CameraShakeData cameraShakeData;	/// カメラ揺れのデータ

	AttackData()
	{
		timing				= AttackTiming();
		colData				= CollisionData();
		damageData			= AttackDamageData();
		knockbackData		= KnockbackData();
		moveData			= AttackMoveData();
		effectData			= EffectData();
		soundData			= SoundData();
		cameraShakeData		= CameraShakeData();
	}
};