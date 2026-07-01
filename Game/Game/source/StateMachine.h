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
	void ChangeState(std::unique_ptr<IState<TOwner>> newState)
	{
		if(!newState || !m_owner) { return; }

		// 現在のステートから抜けるときの処理を呼び出す
		if(m_currentState) { m_currentState->Exit(m_owner); }

		// 新しいステートに切り替える
		m_currentState = std::move(newState);

		// 新しいステートに入るときの処理を呼び出す
		if(m_currentState) { m_currentState->Enter(m_owner); }
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

private:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// ステートマシンを所有するオーナーの参照
	TOwner* m_owner;

	/// 現在のステートを保持するスマートポインタ
	std::unique_ptr<IState<TOwner>> m_currentState = nullptr;

};