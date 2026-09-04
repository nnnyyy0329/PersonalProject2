#pragma once
#include "MapData.h"
#include "PrimitiveShapeCube.h"
#include "PrimitiveShapePlane.h"
#include "NavigationGrid.h"
#include "math/Math.h"
#include <array>

/// @brief マップクラス
class Map
{
public:

	Map() = default;
	virtual ~Map() = default;

	//=======================================================================
	// 基本関数
	//=======================================================================

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
	void Render();

	//=======================================================================
	// ゲッター
	//=======================================================================

	/// @brief マップデータ取得
	/// 
	/// @return マップデータ
	const MapData::Data& GetMapData() const { return m_mapData; }

	/// @brief 壁のコリジョン情報のvector配列取得
	///
	/// @return 壁のコリジョン情報vectorの配列
	const std::vector<Math::AABB>& GetWallColliders() const { return m_wallColliders; }

	/// @brief ナビゲーショングリッドの取得関数（const版）
	///
	/// @return ナビゲーショングリッドの参照
	const NavigationGrid& GetNavigationGrid() const { return m_navigationGrid; }

	/// @brief ナビゲーショングリッドの取得関数
	///
	/// @return ナビゲーショングリッドの参照
	NavigationGrid& GetNavigationGrid() { return m_navigationGrid; }

private:

	//========================================================================
	// 内部関数
	//========================================================================

	/// @brief ハンドルの初期設定関数
	void InitializeHandle();

	/// @brief 立方体マップを作成する関数
	void CreateCubeMap();

	/// @brief 平面マップを作成する関数
	void CreatePlaneMap();

	//=======================================================================
	// メンバ変数
	//=======================================================================

	/// マップデータ
	MapData::Data m_mapData;

	/// 立方体の形状を表すクラス
	PrimitiveShapeCube m_primitiveShapeCube;

	/// 平面の形状を表すクラス
	PrimitiveShapePlane m_primitiveShapePlane;

	/// ナビゲーショングリッド
	NavigationGrid m_navigationGrid;

	/// 壁のコリジョン情報
	std::vector<Math::AABB> m_wallColliders;

	/// ステージBGM
	int m_stageBgm = -1;

	/// マップのコリジョンハンドル
	int m_mapCollisionHandle = -1;

};

