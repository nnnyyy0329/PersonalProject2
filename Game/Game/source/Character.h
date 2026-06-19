#pragma once
#include "ObjectLogic.h"
#include "ICharacterAction.h"
#include "IComponent.h"
#include <memory>
#include <vector>

class Character;	/// キャラクタークラス

/// コンポーネント基底クラスのエイリアス
using ComponentBase = IComponent<Character>;

/// @brief キャラクタークラス
class Character : public ObjectLogic
{
public:

	Character() = default;
	virtual ~Character() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize() override;

	/// @brief 終了関数
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Terminate() override;

	/// @brief 更新関数
	virtual void Update() override;

	//===========================================================================
	// アクション管理関数
	//===========================================================================

	/// @brief アクションの設定関数
	///
	/// @param newAction 新しいアクション
	void SetAction(std::unique_ptr<ICharacterAction> newAction);

	/// @brief 現在のアクションが指定された型かどうかを判定する関数
	///
	/// @tparam T 判定したいアクションの型
	/// 
	/// @return 現在のアクションが指定された型である場合はtrue、そうでない場合はfalse
	template<typename TAction>
	bool IsCurrentAction()const
	{
		return dynamic_cast<TAction*>(m_currentAction.get()) != nullptr;
	}

	//===========================================================================
	// コンポーネント管理関数
	//===========================================================================

	/// @brief コンポーネントの追加関数
	///
	/// @param component 追加するコンポーネント
	void AddComponent(std::unique_ptr<ComponentBase> component);

	/// @brief コンポーネントの取得関数
	///
	/// @tparam T 取得したいコンポーネントの型
	/// 
	/// @return 取得したいコンポーネントのポインタ。見つからない場合はnullptr
	template<typename T>
	T* GetComponent()
	{
		for(const auto& component : m_components)
		{
			// 型変換(dynamic_cast)を試みる
			T* target = dynamic_cast<T*>(component.get());

			// 目的の型のコンポーネントが見つかった場合、変換したポインタを返す
			if(target) { return target; }
		}

		// 目的の型のコンポーネントが見つからなかった場合、nullptrを返す
		return nullptr;
	}

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief モデルのハンドルを取得する関数
	///
	/// @return モデルのハンドル
	int GetModelHandle() const { return m_data.handle; }

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 現在実行しているアクション
	std::unique_ptr<ICharacterAction> m_currentAction;

	/// キャラクターのコンポーネントを格納するベクター
	std::vector<std::unique_ptr<ComponentBase>> m_components;

};

