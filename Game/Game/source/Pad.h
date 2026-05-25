#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include <utility>

///	@brief 受け取る入力の状態
enum class PadButton
{
	A = PAD_INPUT_1,
	B = PAD_INPUT_2,
	X = PAD_INPUT_3,
	Y = PAD_INPUT_4,
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

	/// @brief パッドが接続されているか
	///
	/// @return 接続されているならtrue、接続されていないならfalse
	bool IsConnected() const { return m_isConnected; }

	//===========================================================================
	// 入力確認処理
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

private:

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

};

