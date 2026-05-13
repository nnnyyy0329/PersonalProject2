#pragma once
#include "appframe.h"

/// @brief ローディングモードクラス
class ModeLoading : public ModeBase
{
	typedef ModeBase base;
public:

	/* 基本関数 */
	virtual bool Initialize();	/// @brief 初期化関数
	virtual bool Terminate();	/// @brief 終了関数

protected:

};

