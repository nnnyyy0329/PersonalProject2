#include "Pad.h"
#include <cmath>
#include <algorithm>

namespace
{
	constexpr int XINPUT_MAX = 32767;		// XInputのスティックの最大値
	constexpr int XINPUT_MIN = -32768;		// XInputのスティックの最小値

	constexpr int DINPUT_HALF_MAX = 500;	// DirectInputのスティックの最大値の半分
	constexpr int DINPUT_MAX = 1000;		// DirectInputのスティックの最大値
	constexpr int DINPUT_MIN = -1000;		// DirectInputのスティックの最小値
}

Pad::Pad()
{
	// ZeroMemory() を使用して、dInput構造体の全てのメンバを0で初期化
	ZeroMemory(&m_dInputState, sizeof(DINPUT_JOYSTATE));

	// ZeroMemory() を使用して、xInput構造体の全てのメンバを0で初期化
	ZeroMemory(&m_xInputState, sizeof(XINPUT_STATE));
}

Pad::~Pad() = default;

void Pad::Update(int padNum)
{
	// パッド番号を保存
	m_padNum = padNum;

	// 接続状態チェック
	CheckConnection(padNum);

	// 入力状態を更新
	m_previousState = m_currentState;

	// 入力状態を更新
	UpdateInputState(padNum);
}

void Pad::CheckConnection(int padNum)
{
	// 取得したパッドの数が、指定されたパッド番号より小さい場合
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

void Pad::UpdateInputState(int padNum)
{
	// 取得したパッドの数が、指定されたパッド番号より大きい場合
	if(GetJoypadNum() >= (padNum + 1))
	{
		// 接続されていると判断
		m_isConnected = true;

		// 現在の入力状態を取得
		m_currentState = GetJoypadInputState(DX_INPUT_PAD1 + padNum);

		// DirectInputの状態を取得
		GetJoypadDirectInputState(DX_INPUT_PAD1 + padNum, &m_dInputState);

		// XInputの状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1 + padNum, &m_xInputState);
	}
	// 接続されていない場合は状態をリセット
	else
	{
		// 接続されていないと判断
		m_isConnected = false;

		// 現在の入力状態をリセット
		m_currentState = 0;

		// DirectInputの状態をリセット
		ZeroMemory(&m_dInputState, sizeof(DINPUT_JOYSTATE));

		// XInputの状態をリセット
		ZeroMemory(&m_xInputState, sizeof(XINPUT_STATE));
	}
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

	// 現在の状態でボタンが押されている場合はホールドと判断
	return (m_currentState & buttonState);
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

double Pad::GetLeftStickX() const
{
	if(!m_isConnected) { return 0.0f; }

	// XInput優先
	if(m_xInputState.ThumbLX != 0)
	{
		// XInputの左スティックのX軸の値を正規化して返す
		return NormalizeStickInput(m_xInputState.ThumbLX, true, false);
	}

	// DirectInputの左スティックのX軸の値を正規化して返す
	return NormalizeStickInput(m_dInputState.X, false, false);
}

double Pad::GetLeftStickY() const
{
	if(!m_isConnected) { return 0.0f; }

	// XInput優先
	if(m_xInputState.ThumbLY != 0)
	{
		// XInputの左スティックのY軸の値を正規化して返す
		return NormalizeStickInput(m_xInputState.ThumbLY, true, true);
	}

	// DirectInputの左スティックのY軸の値を正規化して返す
	return NormalizeStickInput(m_dInputState.Y, false, true);
}

double Pad::GetRightStickX() const
{
	if(!m_isConnected) { return 0.0f; }

	// XInput優先
	if(m_xInputState.ThumbRX != 0)
	{
		// XInputの右スティックのX軸の値を正規化して返す
		return NormalizeStickInput(m_xInputState.ThumbRX, true, false);
	}

	// DirectInputの右スティックのX軸の値を正規化して返す
	return NormalizeStickInput(m_dInputState.Rx, false, false);
}

double Pad::GetRightStickY() const
{
	if(!m_isConnected) { return 0.0f; }

	// XInput優先
	if(m_xInputState.ThumbRY != 0)
	{
		// XInputの右スティックのY軸の値を正規化して返す
		return NormalizeStickInput(m_xInputState.ThumbRY, true, true);
	}

	// DirectInputの右スティックのY軸の値を正規化して返す
	return NormalizeStickInput(m_dInputState.Ry, false, true);
}

double Pad::NormalizeStickInput(int inputValue, bool isXinput, bool isYAxis) const
{
	// 正規化された値を格納する変数
	double normalized = 0.0f;

	// XInputの場合 -32768 〜 32767 の範囲を - 1.0 〜 1.0 に正規化する
	if(isXinput)
	{
		// XInputの値を正規化
		normalized = static_cast<double>(inputValue) / XINPUT_MAX;
	}
	// DirectInputの場合 -1000 〜 1000 の範囲を -1.0 〜 1.0 に正規化する
	else
	{
		// DirectInputの値を正規化
		normalized = (static_cast<double>(inputValue) - DINPUT_HALF_MAX) / DINPUT_HALF_MAX;
	}

	// Y軸の場合は、上方向が正になるように値を反転する
	if(isYAxis)
	{
		// Y軸の値を反転
		normalized *= -1.0;
	}

	// デッドゾーン内の場合
	if(std::abs(normalized) < m_deadZone)
	{
		// デッドゾーン内の値は0にする
		return 0.0f;
	}
	// デッドゾーンを超えた場合、値を 0.0 ~ 1.0 の範囲に再マッピングする
	else
	{
		// 入力値の符号を保存
		double sign = (normalized > 0) ? 1.0 : -1.0;

		// 超えた値からデッドゾーンを引いて、デッドゾーンを除いた残りの範囲で正規化する
		double remapped = (std::abs(normalized) - m_deadZone) / (1.0 - m_deadZone);

		// 符号を戻して返す
		return sign * remapped;
	}
}