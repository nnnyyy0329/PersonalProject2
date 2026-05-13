#pragma once
#include "appframe.h"

/// @brief カメラデータ構造体
struct CameraData
{
	VECTOR pos;	
	VECTOR target;
	VECTOR upVec;
};

/// @brief ゲームカメラクラス
class GameCamera
{
public:

	GameCamera();
	~GameCamera();

	/* 基本関数 */
	bool Initialize();	/// @brief 初期化関数
	bool Terminate();	/// @brief 終了関数
	bool Process();		/// @brief 更新関数

	/* アクセッサ */

	/// @brief カメラの位置を設定
	///
	/// @param pos カメラの位置
	void SetPos(const VECTOR& pos) { m_pos = pos; }

	/// @brief カメラの注視点を設定
	///
	/// @param target カメラの注視点
	void SetTarget(const VECTOR& target) { m_target = target; }

private:

	CameraData m_cameraData;	/// @brief カメラデータ
	VECTOR	m_pos;				/// @brief カメラの位置
	VECTOR	m_target;			/// @brief カメラの注視点
	float	m_clipNear;			/// @brief カメラの近クリップ距離
	float	m_clipFar;			/// @brief カメラの遠クリップ距離

protected:

};

