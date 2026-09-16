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

namespace
{
	// 敵の総数
	constexpr int ENEMY_ALL_NUM = 5;

	// 敵の初期スポーン位置X
	constexpr float ENEMY_DEFAULT_SPAWN_X = -600.0f;

	// 敵の初期スポーン位置Z
	constexpr float ENEMY_DEFAULT_SPAWN_Z = 300.0f;

	// 敵のスポーン時の回転量
	const Vec3::Vector3 ENEMY_SPAWN_ROT = { 0.0f, 4.7f, 0.0f };
}

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
	// 内部関数
	//===========================================================================

	/// @brief 全ての敵が死亡しているかを判定する関数
	///
	/// @return 全ての敵が死亡しているならtrue、そうでないならfalse
	bool IsDeadAllEnemy() const;

	/// @brief プレイヤーが死亡しているかを判定する関数
	///
	/// @return プレイヤーが死亡しているならtrue、そうでないならfalse
	bool IsDeadPlayer() const;

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

	/// @brief 敵専用のオブジェクト生成関数
	void EnemyCreate();

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

