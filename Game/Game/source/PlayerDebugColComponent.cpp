#include "PlayerDebugColComponent.h"
#include "DebugManager.h"
#include "CollisionShapeBuilder.h"

void PlayerDebugColComponent::Update(Character& owner)
{
	// プレイヤーの当たり判定をデバッグ表示
	DrawPlayerCollision(owner);

	// プレイヤーの攻撃判定をデバッグ表示
	DrawPlayerAttackCollision(owner);
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
			auto& charColData = owner.GetCharColData();

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

	// プレイヤーの攻撃コリジョン情報を取得
	auto capsule = CollisionShapeBuilder::CreateAttackCapsule(owner);
	if(!capsule.has_value()) { return; }
	
	// デバッグコリジョンマネージャーに描画関数を追加
	debugCol.AddColItem([capsule]()
		{
			// 3Dカプセルを描画
			DrawCapsule3D
			(
				capsule.value().top,	// カプセルの上端の座標
				capsule.value().bottom,	// カプセルの下端の座標
				capsule.value().radius,	// カプセルの半径
				16,						// カプセルの分割数
				GetColor(255, 0, 0),	// カプセルの色
				GetColor(255, 0, 0),	// カプセルの線の色
				TRUE
			);
		});
}