#include "EnemyDebugColComponent.h"
#include "Character.h"
#include "DebugManager.h"
#include "VectorConverter/VectorConverter.h"
#include "EnemyDetectionComponent.h"

void EnemyDebugColComponent::Update(Character& owner, const GameContext& gameContext)
{
	// 敵の当たり判定をデバッグ表示
	DrawEnemyCollision(owner);

	// 敵の検知範囲をデバッグ表示
	DrawEnemyDetectionRange(owner);

	// 敵の攻撃範囲をデバッグ表示
	DrawEnemyAttackRange(owner);
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
				Vec::ToDxVec(charColData.capsule.start),	// カプセルの上端の座標
				Vec::ToDxVec(charColData.capsule.end),		// カプセルの下端の座標
				charColData.capsule.radius,					// カプセルの半径
				16,											// カプセルの分割数
				GetColor(0, 255, 0),						// カプセルの色
				GetColor(0, 0, 255),						// カプセルの線の色
				TRUE
			);
		});
}

void EnemyDebugColComponent::DrawEnemyDetectionRange(Character& owner)
{
	// 敵の検知コンポーネントを取得
	auto* detectionComp = owner.GetComponent<EnemyDetectionComponent>();
	if (!detectionComp) { return; }

	// デバッグコリジョンマネージャーのインスタンスを取得
	auto& debugCol = DebugManager::GetInstance().GetDebugCollision();
	if(!&debugCol) { return; }

	// デバッグコリジョンマネージャーに描画関数を追加
	debugCol.AddColItem([&owner, detectionComp]()
		{
			// 検知範囲の中心座標を取得
			auto center = owner.GetObjectData().pos;

			// 検知対象キャラの有無に応じて、検知範囲を設定
			auto target = detectionComp->GetTarget();
			float range = 0.0f;
			if(target)
			{
				range = detectionComp->GetLoseRange();
			}
			else
			{
				range = detectionComp->GetDetectRange();
			}

			// 検知範囲の円を描画するための分割数
			constexpr int segmentCount = 64;

			// デバッグ表示の高さを少し上げる
			float debugHeight = 2.0f;

			for(int i = 0; i < segmentCount; ++i)
			{
				float angle1 = DX_PI_F * 2.0f * i / segmentCount;
				float angle2 = DX_PI_F * 2.0f * (i + 1) / segmentCount;

				// 検知範囲の円を描画するための2つの点を計算
				Vec3::Vector3 pos1;
				pos1.SetX(center.GetX() + std::cos(angle1) * range);
				pos1.SetY(center.GetY() + debugHeight);
				pos1.SetZ(center.GetZ() + std::sin(angle1) * range);

				Vec3::Vector3 pos2;
				pos2.SetX(center.GetX() + std::cos(angle2) * range);
				pos2.SetY(center.GetY() + debugHeight);
				pos2.SetZ(center.GetZ() + std::sin(angle2) * range);

				// 2つの点を結ぶ線を描画
				DrawLine3D(
					VGet(pos1.GetX(), pos1.GetY(), pos1.GetZ()),
					VGet(pos2.GetX(), pos2.GetY(), pos2.GetZ()),
					GetColor(255, 255, 0));
			}
		});
}

void EnemyDebugColComponent::DrawEnemyAttackRange(Character& owner)
{
	// 敵の検知コンポーネントを取得
	auto* detectionComp = owner.GetComponent<EnemyDetectionComponent>();
	if(!detectionComp) { return; }

	// デバッグコリジョンマネージャーのインスタンスを取得
	auto& debugCol = DebugManager::GetInstance().GetDebugCollision();
	if(!&debugCol) { return; }

	// デバッグコリジョンマネージャーに描画関数を追加
	debugCol.AddColItem([&owner, detectionComp]()
		{
			// 攻撃範囲の中心座標を取得
			auto center = owner.GetObjectData().pos;

			// 攻撃範囲の半径を取得
			float range = detectionComp->GetAttackRange();

			// 攻撃範囲の円を描画するための分割数
			constexpr int segmentCount = 64;

			// デバッグ表示の高さを少し上げる
			float debugHeight = 2.0f;

			for(int i = 0; i < segmentCount; ++i)
			{
				float angle1 = DX_PI_F * 2.0f * i / segmentCount;
				float angle2 = DX_PI_F * 2.0f * (i + 1) / segmentCount;

				// 攻撃範囲の円を描画するための2つの点を計算
				Vec3::Vector3 pos1;
				pos1.SetX(center.GetX() + std::cos(angle1) * range);
				pos1.SetY(center.GetY() + debugHeight);
				pos1.SetZ(center.GetZ() + std::sin(angle1) * range);

				Vec3::Vector3 pos2;
				pos2.SetX(center.GetX() + std::cos(angle2) * range);
				pos2.SetY(center.GetY() + debugHeight);
				pos2.SetZ(center.GetZ() + std::sin(angle2) * range);

				// 2つの点を結ぶ線を描画
				DrawLine3D(
					VGet(pos1.GetX(), pos1.GetY(), pos1.GetZ()),
					VGet(pos2.GetX(), pos2.GetY(), pos2.GetZ()),
					GetColor(255, 0, 0)
				);
			}
		});
}