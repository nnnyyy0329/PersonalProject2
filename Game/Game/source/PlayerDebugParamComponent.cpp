#include "PlayerDebugParamComponent.h"
#include "Character.h"
#include "DebugManager.h"
#include "HealthComponent.h"

bool PlayerDebugParamComponent::Initialize(Character& owner)
{
	// キャラクターの体力をデバッグ表示する関数を呼び出す
	HealthDebugParam(owner);

	// キャラクターの位置をデバッグ表示する関数を呼び出す
	PositionDebugParam(owner);

	return true;
}

void PlayerDebugParamComponent::HealthDebugParam(Character& owner)
{
	// キャラクターの体力コンポーネントを取得
	auto* health = owner.GetComponent<HealthComponent<Character>>();
	if(!health) { return; }

	// デバッグパラメーターのインスタンスを取得
	auto& debugParam = DebugManager::GetInstance().GetDebugParameter();

	// ラムダ式を使用して、体力のデバッグパラメーターを追加
	debugParam.AddItem("PlayerHealth", [this, health]() { return std::to_string(health->GetLife()); });
	debugParam.AddItem("PlayerMaxHealth", [this, health]() { return std::to_string(health->GetMaxLife()); });
}

void PlayerDebugParamComponent::PositionDebugParam(Character& owner)
{
	// デバッグパラメーターのインスタンスを取得
	auto& debugParam = DebugManager::GetInstance().GetDebugParameter();

	// ラムダ式を使用して、位置のデバッグパラメーターを追加
	debugParam.AddItem("PlayerPosX", [this, &owner]() { return std::to_string(owner.GetObjectData().pos.x); });
	debugParam.AddItem("PlayerPosY", [this, &owner]() { return std::to_string(owner.GetObjectData().pos.y); });
	debugParam.AddItem("PlayerPosZ", [this, &owner]() { return std::to_string(owner.GetObjectData().pos.z); });
}