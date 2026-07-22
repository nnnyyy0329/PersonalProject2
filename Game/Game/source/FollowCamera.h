#pragma once
#include "CameraBase.h"
#include "CameraInput.h"

struct ObjectData;	/// オブジェクトデータ構造体

/// @brief 追従カメラクラス
class FollowCamera : public CameraBase
{
public:

	FollowCamera(const ObjectData& target);
	virtual ~FollowCamera() = default;

	//==========================================================================
	// 基本関数
	//==========================================================================

	/// @brief 更新関数
	void Update() override;

	//==========================================================================
	// 内部関数
	//==========================================================================

	/// @brief カメラの設定を行う関数
	void SetUpCamera() const override;

private:

	//==========================================================================
	// 内部関数
	//==========================================================================

	/// @brief カメラの位置を更新する関数
	void UpdateCameraPosition();

	/// @brief カメラのヨー角のオフセットを計算する関数
	///
	/// @return カメラのヨー角のオフセット
	Vec3::Vector3 CalcYawOffset() const;

	/// @brief カメラのピッチ角のオフセットを計算する関数
	///
	/// @return カメラのピッチ角のオフセット
	Vec3::Vector3 CalcPitchOffset() const;

	/// @brief カメラの回転を更新する関数
	void UpdateCameraRotation();

	//==========================================================================
	// メンバ変数
	//==========================================================================

	/// 追従対象のオブジェクトデータへの参照
	const ObjectData& m_targetObject;

	/// 追従するオブジェクトからカメラへのオフセット
	Vec3::Vector3 m_posOffset = {};

	/// 追従するオブジェクトへのオフセット
	Vec3::Vector3 m_targetOffset = {};

	/// カメラ入力クラス（宣言したヘッダーでインスタンスが生成される）
	CameraInput m_cameraInput;

	/// カメラのヨー角
	float m_yaw = 0.0f;

	/// カメラのピッチ角
	float m_pitch = 0.0f;
};

