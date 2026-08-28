#pragma once

class ObjectManager;	/// オブジェクトマネージャークラス
class CameraManager;	/// カメラマネージャークラス

/// @brief ゲームのコンテキストを管理するクラス
class GameContext
{
public:

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief オブジェクトマネージャークラスの参照を取得する関数
	///
	/// @return オブジェクトマネージャークラスの参照
	ObjectManager& GetObjectManager() const;

	/// @brief カメラマネージャークラスの参照を取得する関数
	///
	/// @return カメラマネージャークラスの参照
	CameraManager& GetCameraManager() const;

	//===========================================================================
	// セッター
	//===========================================================================

	/// @brief オブジェクトマネージャークラスの参照用ポインタを設定する関数
	///
	/// @param objectManager 設定するオブジェクトマネージャークラスの参照用ポインタ
	void SetObjectManager(ObjectManager* objectManager) { m_objectManager = objectManager; }

	/// @brief カメラマネージャークラスの参照用ポインタを設定する関数
	///
	/// @param cameraManager 設定するカメラマネージャークラスの参照用ポインタ
	void SetCameraManager(CameraManager* cameraManager) { m_cameraManager = cameraManager; }

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// オブジェクトマネージャークラスの参照用ポインタ
	ObjectManager* m_objectManager = nullptr;

	/// カメラマネージャークラスの参照用ポインタ
	CameraManager* m_cameraManager = nullptr;

};

