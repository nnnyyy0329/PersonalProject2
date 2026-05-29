#pragma once
#include "appframe.h"

class ObjectLogic;	/// オブジェクトのロジッククラス

/// @brief ゲーム内のオブジェクトの生成クラス
class ObjectFactory
{
public:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief オブジェクト生成関数の型を定義
	using CreateFunc = std::function<std::unique_ptr<ObjectLogic>()>;

	/// @brief オブジェクトの登録関数
	///
	/// @param name オブジェクトの名前
	/// @param func オブジェクトの生成関数
	void RegisterObject(const std::string& name, CreateFunc func);

	/// @brief オブジェクトの生成関数
	///
	/// @param name オブジェクトの名前
	/// 
	/// @return 生成されたオブジェクトのロジッククラスのユニークポインタ
	std::unique_ptr<ObjectLogic> CreateObject(const std::string& name);

private:
	
	//===========================================================================
	// メンバ変数
	//===========================================================================

	std::unordered_map<std::string, CreateFunc> m_objectCreators;	/// オブジェクトの登録マップ

};

