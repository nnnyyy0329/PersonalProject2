#pragma once
#include "ObjectLogic.h"
#include "CharacterData.h"
#include "ICharacterAction.h"
#include "IComponent.h"
#include <memory>
#include <vector>
#include <cmath>

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
	///
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(const GameContext& gameContext) override;

	//===========================================================================
	// アクション管理関数
	//===========================================================================

	/// @brief アクションの更新関数
	void UpdateActions();

	/// @brief アクションの設定関数
	///
	/// @param newAction 新しいアクション
	void SetAction(std::unique_ptr<ICharacterAction> newAction);

	/// @brief 現在のアクションの取得関数
	///
	/// @tparam TAction 取得したいアクションの型
	/// 
	/// @return 現在のアクションのポインタ。現在のアクションが指定された型でない場合はnullptr
	template<typename TAction>
	TAction* GetCurrentAction()
	{
		return dynamic_cast<TAction*>(m_currentAction.get());
	}

	/// @brief 現在のアクションが指定された型かどうかを判定する関数
	///
	/// @tparam TAction 判定したいアクションの型
	/// 
	/// @return 現在のアクションが指定された型である場合はtrue、そうでない場合はfalse
	template<typename TAction>
	bool IsCurrentAction()const
	{
		return dynamic_cast<TAction*>(m_currentAction.get()) != nullptr;
	}

	/// @brief デフォルトのアクションを作成する関数
	///
	/// @return デフォルトのアクションのポインタ
	virtual std::unique_ptr<ICharacterAction> CreateDefaultAction() = 0;

	//===========================================================================
	// コンポーネント管理関数
	//===========================================================================

	/// @brief コンポーネントの更新関数
	///
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	void UpdateComponents(const GameContext& gameContext);

	/// @brief コンポーネントの追加関数
	///
	/// @param component 追加するコンポーネント
	void AddComponent(std::unique_ptr<ComponentBase> component);

	/// @brief コンポーネントの取得関数
	///
	/// @tparam TComponent 取得したいコンポーネントの型
	/// 
	/// @return 取得したいコンポーネントのポインタ。見つからない場合はnullptr
	template<typename TComponent>
	TComponent* GetComponent()
	{
		for(const auto& component : m_components)
		{
			// 型変換(dynamic_cast)を試みる
			TComponent* target = dynamic_cast<TComponent*>(component.get());

			// 目的の型のコンポーネントが見つかった場合、変換したポインタを返す
			if(target) { return target; }
		}

		// 目的の型のコンポーネントが見つからなかった場合、nullptrを返す
		return nullptr;
	}

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief キャラクターの前方向ベクトルを取得する関数
	///
	/// @return キャラクターの前方向ベクトル
	Vec3::Vector3 GetForward() const;

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief モデルのハンドルを取得する関数
	///
	/// @return モデルのハンドル
	int GetModelHandle() const { return m_data.handle; }

	/// @brief キャラクターの当たり判定データの取得関数
	///
	/// @return キャラクターの当たり判定データ
	const CharColData& GetCharColData() const { return m_charColData; }

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 現在実行しているアクション
	std::unique_ptr<ICharacterAction> m_currentAction;

	/// キャラクターのコンポーネントを格納するベクター
	std::vector<std::unique_ptr<ComponentBase>> m_components;

	/// キャラクターの当たり判定データ
	CharColData m_charColData;

};

