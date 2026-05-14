#pragma once
#include "appframe.h"

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

struct LightData
{
	LIGHT_TYPE type;	/// @brief ライトの種類
	LIGHT_STATE state;	/// @brief ライトの状態
	VECTOR position;	/// @brief ライトの位置
	VECTOR direction;	/// @brief ライトの方向
	float intensity;	/// @brief ライトの強度

	/// @brief ライトデータコンストラクタ
	LightData()
	{
		type		= LIGHT_TYPE::DIRECTIONAL;
		state		= LIGHT_STATE::INACTIVE;
		position	= VGet(0, 0, 0);
		direction	= VGet(-1.0f, -1.0f, -1.0f);
		intensity	= 1.0f;
	}
};

/// @brief ライトクラス
class Light
{
public:

	Light();
	virtual ~Light();

	/* 基本関数 */
	bool Initialize();	/// @brief 初期化関数
	bool Terminate();	/// @brief 終了関数
	bool Process();		/// @brief 更新関数


	/* 内部関数 */

	/// @brief ライトデータ取得
	///
	/// @return ライトデータ
	const LightData& GetLightData() const { return m_lightData; }

protected:

	LightData m_lightData;	/// @brief ライトデータ

};

