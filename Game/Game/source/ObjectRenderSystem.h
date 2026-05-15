#pragma once
#include "ObjectData.h"
#include "Map.h"
#include "Light.h"

/// @brief ゲーム内のオブジェクトの描画クラス
class ObjectRenderSystem
{
public:

	ObjectRenderSystem();
	virtual ~ObjectRenderSystem();

	//=======================================================================
	// 描画関数
	//=======================================================================


	/// @brief 描画開始
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	void BeginRender();

	/// @brief 描画終了
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	void EndRender();

    /// @brief オブジェクト描画
    /// 
    /// @param data オブジェクトデータ
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	void ObjectRender(const ObjectData& data);

    /// @brief マップ描画
    /// 
    /// @param map マップ
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	void MapRender(const Map& map);

	/// @brief ライト描画
	///
	/// @param light ライト
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	void LightRender(const Light& light);

protected:

	//=======================================================================
	// メンバ変数
	//=======================================================================

};

