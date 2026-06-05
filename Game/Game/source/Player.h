#pragma once
#include "Character.h"

/// @brief プレイヤークラス
class Player : public Character
{
public:

	Player();
	virtual ~Player();
	
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
	virtual void Update() override;

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief コンポーネントの設定関数
	void SetUpComponents();

	/// @brief アクションの設定関数
	void SetUpActions();

};

