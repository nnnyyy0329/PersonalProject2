#pragma once
#include "Vector/Vector3.h"

/// @brief ライトの種類列挙型
enum class LIGHT_TYPE
{
	POINT,			///< 点光源
	DIRECTIONAL,	///< 平行光源
	SPOT,			///< スポットライト
};

/// @brief ライトの状態列挙型
enum class LIGHT_STATE
{
	ACTIVE,		///< ライトが有効
	INACTIVE,	///< ライトが無効
};

/// @brief ライトデータ構造体
struct LightData
{
	LIGHT_TYPE type;			/// ライトの種類
	LIGHT_STATE state;			/// ライトの状態
	Vec3::Vector3 position;		/// ライトの位置
	Vec3::Vector3 direction;	/// ライトの方向
	float intensity;			/// ライトの強度

	LightData()
	{
		type = LIGHT_TYPE::DIRECTIONAL;
		state = LIGHT_STATE::INACTIVE;
		position = Vec3::Vector3(0.0f, 0.0f, 0.0f);
		direction = Vec3::Vector3(-1.0f, -1.0f, 0.5f);
		intensity = 1.0f;
	}
};