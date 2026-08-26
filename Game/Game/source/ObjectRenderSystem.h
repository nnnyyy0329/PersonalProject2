#pragma once
#include "ObjectData.h"
#include "Map.h"
#include "Light.h"
#include "ShadowMapRenderer.h"

/// @brief ゲーム内のオブジェクトの描画クラス
class ObjectRenderSystem
{
public:

	ObjectRenderSystem() = default;
	virtual ~ObjectRenderSystem() = default;

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

	//=======================================================================
	// 描画関数
	//=======================================================================

	/// @brief 描画開始
	void BeginRender();

	/// @brief 描画終了
	void EndRender();

    /// @brief オブジェクト描画
    /// 
    /// @param data オブジェクトデータ
	void ObjectRender(const ObjectData& data);

    /// @brief マップ描画
    /// 
    /// @param map マップ
	void MapRender(const Map& map);

	/// @brief ライト描画
	///
	/// @param light ライト
	void LightRender(const Light& light);

	//=======================================================================
	// シャドウマップ描画関数
	//=======================================================================

	/// @brief シャドウマップ描画開始
	///
	/// @param light ライト
	void BeginShadowRender(const Light& light);

	/// @brief シャドウマップ描画終了
	void EndShadowRender();

	/// @brief オブジェクトのシャドウマップ描画
	///
	/// @param data オブジェクトデータ
	void ObjectShadowRender(const ObjectData& data);

	/// @brief マップのシャドウマップ描画
	///
	/// @param map マップ
	void MapShadowRender(const Map& map);

	/// @brief 通常描画時にシャドウマップを有効化する
	void SetShadowMap();

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// シャドウマップ描画クラス
	ShadowMapRenderer m_shadowMapRenderer;

	/// ライトの方向
	Vec3::Vector3 m_lightDirection = { 0.0f, 0.0f, 0.0f };

};

