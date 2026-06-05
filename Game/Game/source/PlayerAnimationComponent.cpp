#include "PlayerAnimationComponent.h"
#include "DxLibAnimationComponent.h"
#include "MoveComponent.h"

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

	// プレイヤーのアニメーションを登録
	RegisterPlayerAnimations(owner);

	return true;
}

void PlayerAnimationComponent::Update(Character& owner)
{
	if(!m_animationComponent) { return; }
	
	// 移動ベクトルに応じてアニメーションを切り替える
	ChangeAnimByMovement();
}

void PlayerAnimationComponent::ChangeAnimByMovement()
{
	if(!m_moveComponent) { return; }

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