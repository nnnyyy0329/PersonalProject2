#include "appframe.h"
#include "ObjectLogic.h"
#include "ObjectRenderSystem.h"
#include "Map.h"
#include "GameCamera.h"

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


private:

	std::vector<std::unique_ptr<ObjectLogic>>	m_objects;	/// ゲーム内のオブジェクトのロジッククラスのリスト
	ObjectRenderSystem							m_render;	/// ゲーム内のオブジェクトの描画クラス
	Map											m_map;		/// ゲーム内のマップクラス
	GameCamera									m_camera;	/// ゲーム内のカメラクラス

}; 
