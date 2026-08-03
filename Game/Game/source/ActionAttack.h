#pragma once
#include "ICharacterAction.h"
#include "AttackData.h"
#include "AttackLunge.h"
#include <unordered_set>

class Character;	/// キャラクタークラス

/// @brief 攻撃アクションクラス
class ActionAttack : public ICharacterAction
{
public:

	ActionAttack(const AttackData& attackData) : m_attackData(attackData) {}
	virtual ~ActionAttack() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief アクションの実行関数
	///
	/// @param character アクションを実行するキャラクター
	virtual void Update(Character& character) override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃がコンボを受付中かどうか
	///
	/// @return コンボを受付中である場合はtrue、そうでない場合はfalse
	bool IsCancelable() const { return m_isCancelable; }

	/// @brief 攻撃が終了しているかどうか
	///
	/// @return 攻撃が終了している場合はtrue、そうでない場合はfalse
	bool IsFinished() const override { return m_isFinished; }

	//===========================================================================
	// ヒット管理関数
	//===========================================================================

	/// @brief 攻撃がヒットしたキャラクターを登録する関数
	///
	/// @param character 登録するキャラクター
	void RegisterHitCharacter(Character* character){ m_hitAttackCharacters.insert(character); }

	/// @brief 攻撃がヒットしたキャラかどうかを判定する関数
	///
	/// @param character 判定したいキャラクター
	/// 
	/// @return 攻撃がヒットしたキャラクターである場合はtrue、そうでない場合はfalse
	bool HasHitCharacter(Character* character) const{ return m_hitAttackCharacters.contains(character); }

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 攻撃のデータを取得する関数
	///
	/// @return 攻撃のデータ
	const AttackData& GetAttackData() const { return m_attackData; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 攻撃が開始されていないときの処理
	void NonePhaseProcess();

	/// @brief コンボ受付時間かを更新する関数
	void UpdateComboReceive();

	/// @brief 攻撃のフェーズを更新する関数
	///
	/// @param character 攻撃を実行するキャラクター
	void UpdateAttackPhase(Character& character);

	/// @brief コリジョンの有効化関数
	///
	/// @param character 攻撃を実行するキャラクター
	void EnableCollision(Character& character);




	/// @brief 攻撃が終了したときの処理関数
	///
	/// @param attackData 攻撃のデータ
	/// @param character 攻撃を実行するキャラクター
	void OnAttackActive(const AttackData& attackData, Character& character);




	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 攻撃時に前方へ踏み込む処理を行うクラスのポインタ
	AttackLunge m_attackLunge;

	/// 攻撃のデータ
	AttackData m_attackData;

	/// 攻撃の現在のフェーズ
	AttackPhase m_currentPhase = AttackPhase::NONE;

	/// 現在のフェーズの経過時間
	float m_stateTime = 0.0f;

	/// 攻撃がキャンセル可能かどうか
	bool m_isCancelable = false;

	/// 攻撃が終了しているかどうか
	bool m_isFinished = false;

	/// 攻撃がヒットしたキャラクターの集合
	std::unordered_set<Character*> m_hitAttackCharacters;
};

