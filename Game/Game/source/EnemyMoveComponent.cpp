#include "EnemyMoveComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "NavigationGrid.h"

namespace
{
	constexpr float MOVE_SPEED = 1.9f;	// 移動速度

	// この距離以上ターゲットが動いたら経路を再計算
	constexpr float REPATH_DISTANCE = 100.0f;

	// ウェイポイント到達判定
	constexpr float WAYPOINT_REACH_DISTANCE = 20.0f;

	// 経路再計算の間隔
	constexpr int REPATH_WAIT_FRAMES = 15;
}

bool EnemyMoveComponent::UpdatePath(
	const Vec3::Vector3& startPos,
	const Vec3::Vector3& targetPos)
{
	if(!m_navigationGrid)
	{
		return false;
	}

	if(m_repathWaitFrame > 0)
	{
		--m_repathWaitFrame;
	}

	// 現在のウェイポイントに到達したか確認
	AdvancePathPoint();

	bool needRebuild = false;

	// 経路がない場合は作成する
	if(!HasPath())
	{
		needRebuild = true;
	}

	// プレイヤーが大きく移動した場合は再計算する
	Vec3::Vector3 targetDiff =
		targetPos - m_lastTargetPos;

	targetDiff.SetY(0.0f);

	if(targetDiff.Length() >= REPATH_DISTANCE &&
	   m_repathWaitFrame <= 0)
	{
		needRebuild = true;
	}

	if(!needRebuild)
	{
		return HasPath();
	}

	m_path =
		m_navigationGrid->FindPath(
			startPos,
			targetPos);

	m_pathIndex = 0;
	m_lastTargetPos = targetPos;
	m_repathWaitFrame = REPATH_WAIT_FRAMES;

	return HasPath();
}

void EnemyMoveComponent::ClearPath()
{
	m_path.clear();
	m_pathIndex = 0;

	m_moveVector =
		Vec3::Vector3(0.0f, 0.0f, 0.0f);
}

bool EnemyMoveComponent::HasPath() const
{
	return m_pathIndex < m_path.size();
}

Vec3::Vector3 EnemyMoveComponent::GetNextPathPoint() const
{
	if(!HasPath())
	{
		return GetOwner()->GetObjectData().pos;
	}

	return m_path[m_pathIndex];
}

void EnemyMoveComponent::AdvancePathPoint()
{
	if(!HasPath())
	{
		return;
	}

	const Vec3::Vector3 currentPos =
		GetOwner()->GetObjectData().pos;

	Vec3::Vector3 difference =
		m_path[m_pathIndex] - currentPos;

	difference.SetY(0.0f);

	if(difference.Length() <= WAYPOINT_REACH_DISTANCE)
	{
		++m_pathIndex;
	}
}

void EnemyMoveComponent::MoveToTarget(
	const Vec3::Vector3& targetPos)
{
	Vec3::Vector3 currentPos =
		GetOwner()->GetObjectData().pos;

	Vec3::Vector3 direction =
		targetPos - currentPos;

	direction.SetY(0.0f);

	float length = direction.Length();

	if(length <= 0.0f)
	{
		m_moveVector =
			Vec3::Vector3(0.0f, 0.0f, 0.0f);

		return;
	}

	direction =
		direction * (1.0f / length);

	m_moveVector = direction * MOVE_SPEED;
}

//void EnemyMoveComponent::MoveToTarget(const Vec3::Vector3& targetPos)
//{
//	// 現在の位置を取得
//	Vec3::Vector3 currentPos = GetOwner()->GetObjectData().pos;
//
//	// 目標位置への方向ベクトルを計算
//	Vec3::Vector3 direction = targetPos - currentPos;
//	direction.SetY(0.0f);
//
//	// 方向ベクトルを正規化
//	float length = direction.Length();
//	if(length > 0.0f){ direction = direction * (1.0f / length); }
//
//	// 移動ベクトルを設定
//	m_moveVector = direction * MOVE_SPEED;
//}