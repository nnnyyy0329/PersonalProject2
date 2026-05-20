#pragma once
#include "appframe.h"

/// @brief カメラデータ構造体
struct CameraData
{
	VECTOR pos;		///< カメラの位置
	VECTOR target;	///< カメラの注視点
	VECTOR upVec;	///< カメラのアップベクトル
};

/// @brief ゲームカメラクラス
class GameCamera
{
public:

	GameCamera();
	virtual ~GameCamera();

	//==========================================================================
	// 基本関数
	//==========================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize();

	/// @brief 終了関数
	///
	///	@return 成功しているならtrue、失敗しているならfalse
	bool Terminate();

	/// @brief 更新関数
	void Process();

	//==========================================================================
	// 内部関数
	//==========================================================================

	/// @brief カメラの設定を行う関数
	void SetUpCamera() const;

	//==========================================================================
	// ゲッター
	//==========================================================================

	/// @brief カメラデータ取得
	///
	/// @return カメラデータ
	const CameraData& GetCameraData() const { return m_cameraData; }

	//==========================================================================
	// セッター
	//==========================================================================

	/// @brief カメラの位置を設定
	///
	/// @param pos カメラの位置
	void SetPos(const VECTOR& pos) { m_cameraData.pos = pos; }

	/// @brief カメラの注視点を設定
	///
	/// @param target カメラの注視点
	void SetTarget(const VECTOR& target) { m_cameraData.target = target; }

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// カメラデータ
	CameraData m_cameraData;

	/// カメラの近クリップ距離
	float	m_clipNear	= 2.0f;		

	/// カメラの遠クリップ距離
	float	m_clipFar	= 10000.0f;	

protected:

};

