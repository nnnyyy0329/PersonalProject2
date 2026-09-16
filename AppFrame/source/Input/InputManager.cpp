#include "InputManager.h"

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

InputManager::InputManager()
{
	// 最大パッド数分の空きを事前に確保しておく
	m_pads.reserve(MAX_PADS);

	// イテレータでmake_uniqueはできないため、ループで生成してベクターに追加する
	for(int i = 0; i < MAX_PADS; ++i)
	{
		// 生成してベクターに追加
		m_pads.push_back(std::make_unique<Pad>());
	}
}

void InputManager::Update()
{
	// イテレータでないのは、パッドの更新関数がパッド番号を引数に取るため
	for(int i = 0; i < MAX_PADS; ++i)
	{
		// パッドの更新関数を呼び出す
		m_pads[i]->Update(i);
	}
}

const Pad& InputManager::GetPad(int padIndex) const
{
	// インデックスが有効な範囲内かチェック
	if(padIndex < 0 || padIndex >= MAX_PADS)
	{
		// 不正なインデックスの場合は0番のパッドを返す
		return *m_pads[0];
	}

	// 有効なインデックスの場合は対応するパッドを返す
	return *m_pads[padIndex];
}