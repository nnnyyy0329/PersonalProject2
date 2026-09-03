#pragma once
#include "MapData.h""
#include "PrimitiveShapeCube.h"

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

protected:

	//=======================================================================
	// メンバ変数
	//=======================================================================

	/// マップデータ
	MapData m_mapData;

	/// 立方体の形状を表すクラス
	PrimitiveShapeCube m_primitiveShapeCube;

	/// ステージBGM
	int m_stageBgm;

	/// マップのコリジョンハンドル
	int m_mapCollisionHandle;

};

