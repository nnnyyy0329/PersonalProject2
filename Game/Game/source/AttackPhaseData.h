#pragma once

/// @brief 攻撃のフェーズを表す列挙型
enum class AttackPhase
{
	NONE,
	STARTUP,	///< 攻撃開始
	ACTIVE,		///< 攻撃が有効
	RECOVERY,	///< 攻撃後の硬直
	ALL			///< 全てのフェーズ
};