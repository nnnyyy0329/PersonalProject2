#include "PlayerDebugColComponent.h"
#include "Character.h"
#include "DebugManager.h"
#include "ActionAttack.h"

bool PlayerDebugColComponent::Initialize(Character& owner)
{
	// プレイヤーの当たり判定をデバッグ表示する関数を呼び出す
	DrawPlayerCollision(owner);

	// プレイヤーの攻撃判定をデバッグ表示する関数を呼び出す
	DrawPlayerAttackCollision(owner);

	return true;
}

void PlayerDebugColComponent::DrawPlayerCollision(const Character& owner)
{
	// デバッグコリジョンマネージャーのインスタンスを取得
	auto& debugCol = DebugManager::GetInstance().GetDebugCollision();
	if(!&debugCol) { return; }

	// デバッグコリジョンマネージャーに描画関数を追加
	debugCol.AddColItem([&owner]()
		{
			// プレイヤーの当たり判定データを取得
			const auto& charColData = owner.GetCharColData();

			// 3Dカプセルを描画
			DrawCapsule3D
			(
				charColData.top,		// カプセルの上端の座標
				charColData.bottom,		// カプセルの下端の座標
				charColData.radius,		// カプセルの半径
				16,						// カプセルの分割数
				GetColor(0, 255, 0),	// カプセルの色
				GetColor(0, 0, 255),	// カプセルの線の色
				TRUE
			);
		});
}

void PlayerDebugColComponent::DrawPlayerAttackCollision(Character& owner)
{
	// デバッグコリジョンマネージャーのインスタンスを取得
	auto& debugCol = DebugManager::GetInstance().GetDebugCollision();
	if(!&debugCol) { return; }
}