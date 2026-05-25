#include "Pad.h"

Pad::Pad() = default;

Pad::~Pad() = default;

void Pad::Update(int padNum)
{
	// パッド番号を保存
	m_padNum = padNum;

	// 接続状態チェック
	CheckConnection(padNum);

	// 入力状態を更新
	m_previousState = m_currentState;

	// 接続されている場合、現在の入力状態を取得
	m_currentState = GetJoypadInputState(DX_INPUT_PAD1 + padNum);
}

void Pad::CheckConnection(int padNum)
{
	// パッド番号が接続されている数より大きい場合
	// +1するのは、パッド番号が0から始まるため
	if(GetJoypadNum() < (padNum + 1))
	{
		// 接続されていないと判断
		m_isConnected = false;

		// 入力状態をリセット
		m_currentState = 0;

		return;
	}

	// 接続されていると判断
	m_isConnected = true;
}

bool Pad::isTrigger(PadButton button) const
{
	// パッドが接続されていない場合は常にfalseを返す
	if(!m_isConnected) { return false; }

	// ボタンの状態を取得
	// std::to_underlying() を使用して、PadButton列挙型の値を整数に変換
	int buttonState = std::to_underlying(button);

	// 現在の状態でボタンが押されていて、前の状態では押されていない場合はトリガーと判断
	return (m_currentState & buttonState) && !(m_previousState & buttonState);
}

bool Pad::isHold(PadButton button) const
{
	// パッドが接続されていない場合は常にfalseを返す
	if(!m_isConnected) { return false; }

	// ボタンの状態を取得
	// std::to_underlying() を使用して、PadButton列挙型の値を整数に変換
	int buttonState = std::to_underlying(button);

	// 現在の状態でボタンが押されていて、前の状態でも押されている場合はホールドと判断
	return (m_currentState & buttonState) && (m_previousState & buttonState);
}

bool Pad::isRelease(PadButton button) const
{
	// パッドが接続されていない場合は常にfalseを返す
	if(!m_isConnected) { return false; }

	// ボタンの状態を取得
	// std::to_underlying() を使用して、PadButton列挙型の値を整数に変換
	int buttonState = std::to_underlying(button);

	// 現在の状態でボタンが押されておらず、前の状態で押されていた場合はリリースと判断
	return !(m_currentState & buttonState) && (m_previousState & buttonState);
}