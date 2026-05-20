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

/// @brief ライトデータ構造体
struct LightData
{
	LIGHT_TYPE type;	///< ライトの種類
	LIGHT_STATE state;	///< ライトの状態
	VECTOR position;	///< ライトの位置
	VECTOR direction;	///< ライトの方向
	float intensity;	///< ライトの強度

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

	//=======================================================================
	// 基本関数
	//=======================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize();	

	/// @brief 終了関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Terminate();

	/// @brief 更新関数
	void Process();

	//=======================================================================
	// 内部関数
	//=======================================================================



	//=======================================================================
	// ゲッター
	//=======================================================================

	/// @brief ライトデータ取得
	///
	/// @return ライトデータ
	const LightData& GetLightData() const { return m_lightData; }

	//=======================================================================
	// セッター
	//=======================================================================

	



protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================


	LightData m_lightData;	/// ライトデータ

};

