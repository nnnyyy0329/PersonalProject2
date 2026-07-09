#pragma once
#include "IState.h"
#include <memory>

/// @brief ステートマシンクラス
///
/// @tparam TOwner ステートマシンを所有するクラスの型
template<typename TOwner>
class StateMachine
{
public:

	virtual ~StateMachine() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ステートの切り替えを行う関数
	///
	/// @param newState 新しいステートのスマートポインタ
	void ChangeState(TOwner& owner, std::unique_ptr<IState<TOwner>> newState)
	{
		if(!newState) { return; }

		// 現在のステートから抜けるときの処理を呼び出す
		if(m_currentState) { m_currentState->Exit(owner); }

		// 新しいステートに切り替える
		m_currentState = std::move(newState);

		// 新しいステートに入るときの処理を呼び出す
		if(m_currentState) { m_currentState->Enter(owner); }
	}

	/// @brief ステートマシンの更新関数
	///
	/// @param owner ステートマシンを所有するオーナー
	void Update(TOwner& owner)
	{
		if(!m_currentState) { return; }

		// 現在のステートの更新関数を呼び出す
		m_currentState->Update(owner);
	}

	/// @brief 現在のステートが指定された型と同じかどうかを判定する関数
	///
	/// @tparam TState 判定したいステートの型
	/// 
	/// @return 現在のステートが指定された型である場合はtrue、そうでない場合はfalse
	template<typename TState>
	bool IsCurrentState()const
	{
		return dynamic_cast<TState*>(m_currentState.get()) != nullptr;
	}

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 現在のステートを取得する関数
	///
	/// @return 現在のステートのポインタ
	IState<TOwner>* GetCurrentState() const { return m_currentState.get(); }

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 現在のステートを保持するスマートポインタ
	std::unique_ptr<IState<TOwner>> m_currentState = nullptr;

};