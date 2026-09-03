#pragma once
#include "MapData.h""
#include "PrimitiveShapeCube.h"
#include "PrimitiveShapePlane.h"

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
	const MapData& GetMapData() const { return m_mapData; }

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
	MapData m_mapData;

	/// 立方体の形状を表すクラス
	PrimitiveShapeCube m_primitiveShapeCube;

	/// 平面の形状を表すクラス
	PrimitiveShapePlane m_primitiveShapePlane;

	/// ステージBGM
	int m_stageBgm = -1;

	/// マップのコリジョンハンドル
	int m_mapCollisionHandle = -1;

};

