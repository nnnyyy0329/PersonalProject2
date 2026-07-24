#include "EnemyDebugColComponent.h"
#include "Character.h"
#include "DebugManager.h"
#include "VectorConverter/VectorConverter.h"

void EnemyDebugColComponent::Update(Character& owner, const GameContext& gameContext)
{
	// 敵の当たり判定をデバッグ表示
	DrawEnemyCollision(owner);
}

void EnemyDebugColComponent::DrawEnemyCollision(const Character& owner)
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
				Vec::ToDxVec(charColData.top),		// カプセルの上端の座標
				Vec::ToDxVec(charColData.bottom),	// カプセルの下端の座標
				charColData.radius,					// カプセルの半径
				16,									// カプセルの分割数
				GetColor(0, 255, 0),				// カプセルの色
				GetColor(0, 0, 255),				// カプセルの線の色
				TRUE
			);
		});
}
