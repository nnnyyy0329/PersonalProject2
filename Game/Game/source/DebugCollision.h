#pragma once
#include "DxLib.h"
#include "AttackData.h"
#include "CharacterData.h"
#include <functional>

/// @brief コリジョン描画を管理するクラス
class DebugCollision
{
public:

	DebugCollision() = default;
	virtual ~DebugCollision() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief コリジョン描画関数の型定義
	using DrawColFunc = std::function<void()>;

	/// @brief コリジョン描画関数を追加する関数
	void AddColItem(DrawColFunc func);

	/// @brief コリジョン描画関数
	void Render();
	
private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// コリジョン描画関数のリスト
	std::vector<DrawColFunc> m_drawColFuncs;

};

