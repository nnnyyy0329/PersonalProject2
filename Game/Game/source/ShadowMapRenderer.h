#pragma once
#include "DxLib.h"

/// @brief シャドウマップ描画クラス
class ShadowMapRenderer
{
public:
	ShadowMapRenderer() = default;
	~ShadowMapRenderer() = default;

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

	/// @brief シャドウマップ描画開始
	///
	/// @param lightDirection ライトの方向
	void BeginRender(const VECTOR& lightDirection);

	/// @brief シャドウマップ描画終了
	void EndShadowRender();

	/// @brief シャドウマップの使用を解除する関数
	void DisableShadowMap();

	/// @brief シャドウマップをセットする関数
	void SetShadowMap();

	/// @brief シャドウマップのハンドルを取得する関数
	///
	/// @return シャドウマップのハンドル
	int GetHandle() const { return m_shadowMapHandle; }

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// シャドウマップのハンドル
	int m_shadowMapHandle = -1;

};

