#pragma once
#include "ObjectData.h"

/// @brief ゲーム内のオブジェクトのロジックを管理するクラス
class ObjectLogic
{
public:

	ObjectLogic();
	virtual ~ObjectLogic();

	/* 基本関数 */
	virtual bool Initialize() = 0;	/// @brief 初期化関数
	virtual bool Terminate() = 0;	///	@brief 終了関数
	virtual bool Process() = 0;		///	@brief 更新関数

protected:

	ObjectData m_data;	/// @brief オブジェクトのデータ

};

