#pragma once
#include "ObjectData.h"

/// @brief ゲーム内のオブジェクトの描画を管理するクラス
class ObjectRenderSystem
{
public:

	ObjectRenderSystem();
	virtual ~ObjectRenderSystem();

	/* 基本関数 */
	virtual bool Render() = 0;	/// @brief 描画関数

protected:

};

