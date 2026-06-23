#include "Character.h"
#include "PlayerAnimationComponent.h"
#include "DxLibAnimationComponent.h"
#include "MoveComponent.h"



#include "PlayerAttackComponent.h"



namespace
{
	constexpr float RUN_THRESHOLD = 0.9f;	// 走りになるまでの移動ベクトルの大きさの閾値
}

bool PlayerAnimationComponent::Initialize(Character& owner)
{
	// アニメーション管理コンポーネントを取得
	m_animationComponent = owner.GetComponent<DxLibAnimationComponent<Character>>();
	if(!m_animationComponent) { return false; }

	// 移動管理コンポーネントを取得
	m_moveComponent = owner.GetComponent<MoveComponent<Character>>();
	if(!m_moveComponent) { return false; }



	// 攻撃管理コンポーネントを取得
	m_playerAttackComponent = owner.GetComponent<PlayerAttackComponent>();
	if(!m_playerAttackComponent) { return false; }



	// プレイヤーのアニメーションを登録
	RegisterPlayerAnimations(owner);

	return true;
}

void PlayerAnimationComponent::Update(Character& owner)
{
	if(!m_animationComponent) { return; }
	
	// 移動ベクトルに応じてアニメーションを切り替える
	ChangeAnimByMovement();

	// 攻撃の状態に応じてアニメーションを切り替える
	ChangeAnimByAttack();
}

void PlayerAnimationComponent::RegisterPlayerAnimations(Character& owner)
{
	if(!m_animationComponent) { return; }

	// プレイヤーのアニメーションを登録
	m_animationComponent->RegisterAnimation("Nchange_attack_00", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("Nchange_attack_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("Nchange_attack_02", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("Nchange_attack_03", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("Nchange_attack_04", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("player_idle_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("player_walk_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("player_jog_01", owner.GetModelHandle());
}

void PlayerAnimationComponent::ChangeAnimByMovement()
{
	if(!m_moveComponent) { return; }




	if(m_playerAttackComponent->GetComboIndex() > 0)
	{
		// 攻撃中は移動アニメーションを再生しない
		return;
	}




	// 移動ベクトルを取得
	VECTOR moveVector = m_moveComponent->GetMoveVector();

	// 移動ベクトルが走りの閾値より大きい場合
	if(VSize(moveVector) > RUN_THRESHOLD)
	{
		// 走り
		m_animationComponent->PlayAnimation("player_jog_01", {});
	}
	// 移動ベクトルが0より大きい場合
	else if(VSize(moveVector) > 0.0f)
	{
		// 歩き
		m_animationComponent->PlayAnimation("player_walk_01", {});
	}
	// それ以外はアイドル
	else
	{
		m_animationComponent->PlayAnimation("player_idle_01", {});
	}
}

void PlayerAnimationComponent::ChangeAnimByAttack()
{
	if(!m_playerAttackComponent) { return; }

	// 現在の攻撃のコンボインデックスを取得
	int comboIndex = m_playerAttackComponent->GetComboIndex();

	// コンボインデックスに応じてアニメーションを切り替える
	switch(comboIndex)
	{
		case 0:
		{
			break;
		}

		case 1:	// 1段目
		{
			m_animationComponent->PlayAnimation("Nchange_attack_00", {});
			break;
		}

		case 2:	// 2段目
		{
			m_animationComponent->PlayAnimation("Nchange_attack_01", {});
			break;
		}
			
		case 3:	// 3段目
		{
			m_animationComponent->PlayAnimation("Nchange_attack_02", {});
			break;
		}
			
		case 4:	// 4段目
		{
			m_animationComponent->PlayAnimation("Nchange_attack_03", {});
			break;
		}

		case 5:	// 5段目

		{
			m_animationComponent->PlayAnimation("Nchange_attack_04", {});
			break;
		}

		default:
		{
			break;
		}
	}
}