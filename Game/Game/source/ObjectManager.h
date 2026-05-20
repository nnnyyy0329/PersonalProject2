#pragma once
#include <vector>
#include <memory>
#include "appframe.h"
#include "ObjectFactory.h"

class ObjectLogic;			/// オブジェクトのロジッククラス
class ObjectRenderSystem;	/// オブジェクトの描画クラス
class Player;				/// プレイヤークラス

/// @brief オブジェクトを管理するクラス
class ObjectManager
{
public:

	ObjectManager();
	virtual ~ObjectManager();

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize();

	/// @brief 終了関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Terminate();

	/// @brief 更新関数
	void Update();

	/// @brief 描画関数
	///
	/// @param renderSystem 描画システム
	void Render(ObjectRenderSystem& renderSystem);

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief プレイヤーオブジェクトの取得関数
	Player* GetPlayer() const { return m_player.get(); }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief オブジェクトの生成関数を登録する
	void RegisterCreators();

	/// @brief プレイヤー専用のオブジェクト生成関数を登録
	void PlayerCreate();

	//===========================================================================
	// メンバ変数
	//===========================================================================

	std::vector<std::unique_ptr<ObjectLogic>> m_objects;	/// オブジェクトのロジッククラスのリスト
	ObjectFactory m_objectFactory;							/// オブジェクトの生成クラス

	std::unique_ptr<Player> m_player;						/// プレイヤーオブジェクトのユニークポインタ

};

