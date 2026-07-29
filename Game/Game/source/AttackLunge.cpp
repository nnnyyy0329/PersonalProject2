#include "AttackLunge.h"
#include "Character.h"
#include "AttackData.h"

void AttackLunge::Update(C& character, const AMD& attackMoveData, AP currentPhase, float stateTime)
{
	if(attackMoveData.movePhase == currentPhase)
	{
		// 攻撃移動の時間を過ぎたら処理をスキップ
		if(stateTime > attackMoveData.moveTime){ return; }

		// 攻撃時に前方へ踏み込む処理を行う
		MoveLunge(character, attackMoveData);
	}

	if(attackMoveData.movePhase == AP::ALL)
	{
		if(currentPhase == AP::STARTUP || currentPhase == AP::ACTIVE || currentPhase == AP::RECOVERY)
		{
			// 攻撃移動の時間を過ぎたら処理をスキップ
			if(stateTime > attackMoveData.moveTime){ return; }

			// 攻撃時に前方へ踏み込む処理を行う
			MoveLunge(character, attackMoveData);
		}
	}
}

void AttackLunge::MoveLunge(C& character, const AMD& attackMoveData)
{
	// キャラクターのオブジェクトデータを取得する
	ObjectData data = character.GetObjectData();

	// キャラクターの前方向ベクトルを取得する
	Vec3::Vector3 forward = character.GetForward();

	// 移動距離を計算する
	Vec3::Vector3 moveDistance = forward * attackMoveData.moveSpeed;

	// キャラクターの位置を更新する
	data.pos = data.pos + moveDistance;

	// 更新されたオブジェクトデータをキャラクターに設定する
	character.SetObjectData(data);
}