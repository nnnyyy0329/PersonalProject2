#pragma once
#include "ObjectLogic.h"

/// @brief キャラクタークラス
class Character : public ObjectLogic
{
public:
	Character();
	virtual ~Character();

	/* 基本関数 */
	virtual bool Initialize() override;	/// @brief 初期化関数
	virtual bool Terminate() override;	///	@brief 終了関数
	virtual bool Process() override;	///	@brief 更新関数

protected:

};

