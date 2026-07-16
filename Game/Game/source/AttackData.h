#pragma once
#include "AttackTiming.h"
#include "CollisionData.h"
#include "AttackDamageData.h"
#include "HitMoveData.h"
#include "EffectData.h"
#include "SoundData.h"
#include "CameraShakeData.h"

/// @brief 攻撃のフェーズを表す列挙型
enum class AttackPhase
{
	NONE,
	STARTUP,	///< 攻撃開始
	ACTIVE,		///< 攻撃が有効
	RECOVERY	///< 攻撃後の硬直
};

/// @brief 攻撃データ構造体
struct AttackData
{
	AttackTiming timing;				/// 攻撃のタイミングデータ
	CollisionData colData;				/// 当たり判定のデータ
	AttackDamageData damageData;		/// 攻撃ダメージのデータ
	HitMoveData hitMoveData;			/// ヒット時の移動データ
	EffectData effectData;				/// エフェクトのデータ
	SoundData soundData;				/// サウンドのデータ
	CameraShakeData cameraShakeData;	/// カメラ揺れのデータ

	AttackData()
	{
		timing				= AttackTiming();
		colData				= CollisionData();
		damageData			= AttackDamageData();
		hitMoveData			= HitMoveData();
		effectData			= EffectData();
		soundData			= SoundData();
		cameraShakeData		= CameraShakeData();
	}
};