#pragma once

class ObjectManager;	/// オブジェクトマネージャークラス
class CameraManager;	/// カメラマネージャークラス
class NavigationGrid;	/// ナビゲーショングリッドクラス

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

	/// @brief ナビゲーショングリッドクラスの参照を取得する関数
	///
	/// @return ナビゲーショングリッドクラスの参照
	NavigationGrid& GetNavigationGrid() const;

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

	/// @brief ナビゲーショングリッドクラスの参照用ポインタを設定する関数
	///
	/// @param navigationGrid 設定するナビゲーショングリッドクラスの参照用ポインタ
	void SetNavigationGrid(NavigationGrid* navigationGrid) { m_navigationGrid = navigationGrid; }

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// オブジェクトマネージャークラスの参照用ポインタ
	ObjectManager* m_objectManager = nullptr;

	/// カメラマネージャークラスの参照用ポインタ
	CameraManager* m_cameraManager = nullptr;

	/// ナビゲーショングリッドクラスの参照用ポインタ
	NavigationGrid* m_navigationGrid = nullptr;
};

