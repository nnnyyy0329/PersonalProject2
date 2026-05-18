#pragma once
#include "appframe.h"

/// @brief ローディングモードクラス
class ModeLoading : public ModeBase
{
	typedef ModeBase base;
public:

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize() override;

	/// @brief 終了関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Terminate() override;

	/// @brief 更新関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Process() override;

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	bool m_isLoadStarted = false;	/// ロード開始したか
};

