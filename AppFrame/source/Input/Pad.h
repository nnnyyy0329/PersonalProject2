#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <utility>

///	@brief 受け取る入力の状態
enum class PadButton
{
	A		= PAD_INPUT_1,	///< Aボタン
	B		= PAD_INPUT_2,	///< Bボタン
	X		= PAD_INPUT_3,	///< Xボタン
	Y		= PAD_INPUT_4,	///< Yボタン
	LB		= PAD_INPUT_5,	///< LBボタン
	RB		= PAD_INPUT_6,	///< RBボタン
	BACK	= PAD_INPUT_7,	///< BACKボタン
	START	= PAD_INPUT_8,	///< STARTボタン
	LS		= PAD_INPUT_9,	///< Lスティック押し込み
	RS		= PAD_INPUT_10	///< Rスティック押し込み
};

/// @brief パッドクラス
class Pad
{
public:

	Pad();
	virtual ~Pad();

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新処理
	///
	/// @param padNum パッド番号
	void Update(int padNum);

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 接続状態チェック
	///
	/// @param padNum パッド番号
	void CheckConnection(int padNum);

	/// @brief 入力状態を更新する関数
	void UpdateInputState(int padNum);

	/// @brief パッドが接続されているか
	///
	/// @return 接続されているならtrue、接続されていないならfalse
	bool IsConnected() const { return m_isConnected; }

	//===========================================================================
	// ボタン入力処理
	//===========================================================================

	/// @brief ボタンが押されているか
	///
	/// @param button ボタン
	/// 
	/// @return 押されているならtrue、押されていないならfalse
	bool isTrigger(PadButton button) const;

	/// @brief ボタンが押されているか
	///
	/// @param button ボタン
	/// 
	/// @return 押されているならtrue、押されていないならfalse
	bool isHold(PadButton button) const;

	/// @brief ボタンが離されたか
	///
	/// @param button ボタン
	///	
	/// @return 離されたならtrue、離されていないならfalse
	bool isRelease(PadButton button) const;

	//===========================================================================
	// スティック入力処理
	//===========================================================================

	/// @brief 左スティックのX軸の値を取得（-1.0 〜 1.0）
	///
	/// @return 左スティックのX軸の値
	double GetLeftStickX() const;

	/// @brief 左スティックのY軸の値を取得（-1.0 〜 1.0）
	///
	/// @return 左スティックのY軸の値
	double GetLeftStickY() const;

	/// @brief 右スティックのX軸の値を取得（-1.0 〜 1.0）
	///
	/// @return 右スティックのX軸の値
	double GetRightStickX() const;
	
	/// @brief 右スティックのY軸の値を取得（-1.0 〜 1.0）
	///
	/// @return 右スティックのY軸の値
	double GetRightStickY() const;

	void SetDeadZone(double deadZone) { m_deadZone = deadZone; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief スティック入力を正規化する関数
	///
	/// @param inputValue スティックの入力値
	/// @param isXinput XInputのスティックかどうか
	/// @param isYAxis Y軸のスティックかどうか
	/// 
	/// @return 正規化されたスティックの値（-1.0 〜 1.0）
	double NormalizeStickInput(int inputValue, bool isXinput, bool isYAxis) const;

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// パッド番号
	int m_padNum = 0;

	/// 現在のフレームの入力状態
	int m_currentState = 0;

	/// 前のフレームの入力状態
	int m_previousState = 0;

	/// パッドが接続されているか
	bool m_isConnected = false;

	// DirectInputの状態
	DINPUT_JOYSTATE m_dInputState;

	// XInputの状態
	XINPUT_STATE m_xInputState;

	// アナログスティックのデッドゾーン
	double m_deadZone  = 0.2;
};

