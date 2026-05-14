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

	/*描画関数 */

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

protected:

};

