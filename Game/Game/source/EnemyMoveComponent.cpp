#include "EnemyMoveComponent.h"
#include "Character.h"
#include "NavigationGrid.h"
#include "GameContext.h"

namespace
{
	// 移動速度
	constexpr float MOVE_SPEED = 1.9f;

	// この距離以上ターゲットが動いたら経路を再計算
	constexpr float REPATH_DISTANCE = 100.0f;

	// ウェイポイント到達判定
	constexpr float WAYPOINT_REACH_DISTANCE = 20.0f;

	// 経路再計算の間隔
	constexpr int REPATH_WAIT_FRAMES = 15;
}

void EnemyMoveComponent::Update(Character& owner, const GameContext& gameContext)
{
	auto& navigationGrid = gameContext.GetNavigationGrid();
	m_navigationGrid = &navigationGrid;
}

bool EnemyMoveComponent::UpdatePath(const Vec3::Vector3& startPos, const Vec3::Vector3& targetPos)
{
	if(!m_navigationGrid) { return false; }

	if(m_repathWaitFrame > 0)
	{
		// 経路再計算の待機時間を減らす
		--m_repathWaitFrame;
	}

	// 現在のウェイポイントに到達したか確認
	AdvancePathPoint();

	bool needRebuild = false;

	// 経路がない場合
	if(!HasPath())
	{
		// 再計算フラグを立てる
		needRebuild = true;
	}

	// プレイヤーが大きく移動した場合は再計算する
	Vec3::Vector3 targetDiff = targetPos - m_lastTargetPos;
	targetDiff.SetY(0.0f);

	// ターゲットが大きく移動した場合は再計算する
	if(targetDiff.Length() >= REPATH_DISTANCE && m_repathWaitFrame <= 0)
	{
		needRebuild = true;
	}

	// 経路再計算が必要ない場合
	if(!needRebuild)
	{
		// 経路の存在を確認する
		return HasPath();
	}

	// 経路再計算を行う
	m_path = m_navigationGrid->FindPath(startPos, targetPos);

	// 再計算に必要な情報を更新する
	m_pathIndex = 0;
	m_lastTargetPos = targetPos;
	m_repathWaitFrame = REPATH_WAIT_FRAMES;

	// 経路が存在するか確認する
	return HasPath();
}

void EnemyMoveComponent::ClearPath()
{
	m_path.clear();
	m_pathIndex = 0;
	m_moveVector = Vec3::Vector3(0.0f, 0.0f, 0.0f);
}

bool EnemyMoveComponent::HasPath() const
{
	// 経路が存在するか確認する
	return m_pathIndex < m_path.size();
}

Vec3::Vector3 EnemyMoveComponent::GetNextPathPoint() const
{
	// 経路が存在しない場合
	if(!HasPath())
	{
		// 現在の位置を返す
		return GetOwner()->GetObjectData().pos;
	}

	// 現在のウェイポイントを返す
	return m_path[m_pathIndex];
}

void EnemyMoveComponent::AdvancePathPoint()
{
	if(!HasPath()) { return; }

	const Vec3::Vector3 currentPos = GetOwner()->GetObjectData().pos;

	// 現在のウェイポイントを取得
	Vec3::Vector3 difference = m_path[m_pathIndex] - currentPos;
	difference.SetY(0.0f);

	// ウェイポイントに到達している場合
	if(difference.Length() <= WAYPOINT_REACH_DISTANCE)
	{
		// 次のウェイポイントに進む
		++m_pathIndex;
	}
}

void EnemyMoveComponent::MoveToTarget(const Vec3::Vector3& targetPos)
{
	const Vec3::Vector3 currentPos = GetOwner()->GetObjectData().pos;

	// 目標位置への方向ベクトルを計算
	Vec3::Vector3 direction = targetPos - currentPos;
	direction.SetY(0.0f);
	float length = direction.Length();

	// 目標位置が現在位置と同じ場合
	if(length <= 0.0f)
	{
		// 移動ベクトルをゼロにする
		m_moveVector = Vec3::Vector3(0.0f, 0.0f, 0.0f);
		return;
	}

	// 方向ベクトルを正規化
	direction = direction * (1.0f / length);

	// 移動ベクトルを設定
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