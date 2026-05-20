#pragma once
#include "CameraBase.h"

struct ObjectData;	/// オブジェクトデータ構造体

/// @brief 追従カメラクラス
class FollowCamera : public CameraBase
{
public:

	FollowCamera(const ObjectData& target);
	virtual ~FollowCamera();

	//==========================================================================
	// 基本関数
	//==========================================================================

	/// @brief 更新関数
	void Update() override;

	//==========================================================================
	// 内部関数
	//==========================================================================

	/// @brief カメラの位置を更新する関数
	void UpdateCameraPosition();

	/// @brief カメラの設定を行う関数
	void SetUpCamera() const override;

private:

	//==========================================================================
	// メンバ変数
	//==========================================================================

	/// 追従対象のオブジェクトデータへの参照
	const ObjectData& m_targetObject;

	/// 追従するオブジェクトからのオフセット
	VECTOR m_offset;
};

