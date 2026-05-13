#include "appframe.h"

/// @brief ゲームモードクラス
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	/* 基本関数 */
	virtual bool Initialize();	/// @brief 初期化関数
	virtual bool Terminate();	/// @brief 終了関数
	virtual bool Process();		/// @brief 更新関数
	virtual bool Render();		/// @brief 描画関数

protected:



}; 
