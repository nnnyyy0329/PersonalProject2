#include "appframe.h"
#include "ObjectLogic.h"
#include "ObjectRenderSystem.h"
#include "Map.h"
#include "GameCamera.h"

class ObjectFactory;

/// @brief ゲームモードクラス
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	/* 基本関数 */

	/// @brief 初期化関数
	virtual bool Initialize() override;	

	/// @brief 終了関数
	virtual bool Terminate() override;

	/// @brief 更新関数
	virtual bool Process() override;

	/// @brief 描画関数
	virtual bool Render() override;


	/* 内部関数 */

	/// @brief オブジェクト生成関数の登録関数
	void RegisterObjectCreators() const;


protected:


private:

	std::vector<std::unique_ptr<ObjectLogic>>	m_objects;	/// ゲーム内のオブジェクトのロジッククラスのリスト
	ObjectRenderSystem							m_render;	/// ゲーム内のオブジェクトの描画クラス
	ObjectFactory								m_factory;	/// ゲーム内のオブジェクトの生成クラス

	Map											m_map;		/// ゲーム内のマップクラス
	GameCamera									m_camera;	/// ゲーム内のカメラクラス
	

}; 
