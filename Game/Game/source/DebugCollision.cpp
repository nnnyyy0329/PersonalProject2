#include "DebugCollision.h"

void DebugCollision::AddColItem(DrawColFunc func)
{
	m_drawColFuncs.push_back(func);
}

void DebugCollision::Render()
{
	// 登録されたコリジョン描画関数をすべて呼び出す
	for (auto& func : m_drawColFuncs)
	{
		// コリジョン描画関数を呼び出す
		func();
	}

	// 描画関数のリストをクリアする
	m_drawColFuncs.clear();
}