#pragma once
#include "CameraBase.h"

/// @brief オブジェクトデータ構造体の前方宣言
struct ObjectData;

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

	/// @brief カメラの設定を行う関数
	void SetUpCamera() const override;

private:

	//==========================================================================
	// メンバ変数
	//==========================================================================

	const ObjectData& m_targetObject;	/// 追従対象のオブジェクトデータへの参照
	VECTOR m_offset;					/// 追従するオブジェクトからのオフセット

};

