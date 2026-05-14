#pragma once
#include "appframe.h"
#include "ObjectLogic.h"

/// @brief ゲーム内のオブジェクトの種類
enum class OBJECT_TYPE
{
	PLAYER,	///< プレイヤー
	ENEMY,	///< 敵
};

/* 前方宣言 */
class Player;

/// @brief ゲーム内のオブジェクトの生成クラス
class ObjectFactory
{
public:

	/// @brief オブジェクト生成関数
	///
	/// @param type 生成するオブジェクトの種類
	/// 
	/// @return 生成されたオブジェクトのロジッククラスのユニークポインタ
	static std::unique_ptr<ObjectLogic> CreateObject(OBJECT_TYPE type);

};

