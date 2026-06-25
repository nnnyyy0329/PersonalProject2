#pragma once
#include <string>
#include <vector>
#include <functional>
#include <utility>

/// @brief デバッグパラメータークラス
class DebugParameter
{
public:

	//===========================================================================	
	// 内部関数
	//===========================================================================

	/// @brief デバッグパラメーターの追加関数
	///
	/// @param name パラメーターの名前
	/// @param getter パラメーターの値を取得する関数
	void AddParamItem(const std::string& name, std::function<std::string()> getter);

	/// @brief デバッグパラメーターの描画関数
	///
	/// @param x 描画位置のX座標
	/// @param y 描画位置のY座標
	void Render(int x, int y);

private:

	//===========================================================================	
	// メンバ変数
	//===========================================================================

	/// デバッグパラメーターのアイテムのベクター
	std::vector<std::pair<std::string, std::function<std::string()>>> m_items;

};

