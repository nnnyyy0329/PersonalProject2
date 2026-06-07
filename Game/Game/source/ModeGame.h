#pragma once
#include "appframe.h"
#include "ObjectRenderSystem.h"
#include "Map.h"

#include "CameraManager.h"
#include "ObjectManager.h"

class Player;	/// プレイヤークラス

/// @brief ゲームモードクラス
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame() = default;
	virtual ~ModeGame() = default;

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
	virtual bool Process() override;

	/// @brief 描画関数
	virtual bool Render() override;

protected:


private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief マネージャーの生成関数
	void CreateManagers();

	/// @brief カメラの生成関数
	void CreateCamera();

	//===========================================================================
	// メンバ変数
	//===========================================================================

	std::unique_ptr<ObjectManager>				m_objectManager;	/// オブジェクトマネージャークラス
	ObjectRenderSystem							m_objectRender;		/// オブジェクトの描画クラス
	Map											m_map;				/// マップクラス

	std::unique_ptr<CameraManager>				m_cameraManager;	/// カメラマネージャークラス

}; 
