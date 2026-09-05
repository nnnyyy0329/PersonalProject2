#pragma once
#include "ObjectFactory.h"
#include <vector>
#include <memory>

class ObjectLogic;			/// オブジェクトのロジッククラス
class ObjectRenderSystem;	/// オブジェクトの描画クラス

class GameContext;			/// ゲームのコンテキストクラス

class Character;			/// キャラクタークラス
class Player;				/// プレイヤークラス
class Enemy;				/// 敵クラス

/// @brief オブジェクトを管理するクラス
class ObjectManager
{
public:

	ObjectManager() = default;
	virtual ~ObjectManager() = default;

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
	void Update(const GameContext& context);

	//===========================================================================
	// 描画関数
	//===========================================================================

	/// @brief 描画関数
	///
	/// @param renderSystem 描画システム
	void ObjectRender(ObjectRenderSystem& renderSystem);

	/// @brief シャドウマップ描画関数
	///
	/// @param renderSystem 描画システム	
	void ShadowRender(ObjectRenderSystem& renderSystem);

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 現在存在しているキャラクターを取得する関数
	///
	/// @return キャラクターのポインタのベクター
	const std::vector<Character*>& GetCharacters();

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

	/// オブジェクトのロジッククラスのリスト
	std::vector<std::unique_ptr<ObjectLogic>> m_objects;

	/// オブジェクトの生成クラス
	ObjectFactory m_objectFactory;

	/// キャラクターのリスト
	std::vector<Character*> m_characters;

	/// プレイヤーオブジェクトのユニークポインタ
	std::unique_ptr<Player> m_player;

};

