#pragma once
#include "IComponent.h"
#include "DxLib.h"
#include <string>
#include <unordered_map>
#include <stdexcept>

/// アニメーション関連の定数
namespace Anim
{
	constexpr float FPS = 60.0f;				// アニメーションのフレームレート
	constexpr float FRAME_RATE = 1.0f/* / FPS*/;	// アニメーションのフレーム時間
}

/// @brief キャラクターのアニメーションを管理するコンポーネントクラス
/// 
/// @tparam TOwner コンポーネントを所有するクラスの型
///	
/// @note ハンドル取得のため、 int GetModelHandle() const; という関数を持つクラスである必要がある
template<typename TOwner>
class DxLibAnimationComponent : public IComponent<TOwner>
{
private:

	/// @brief アニメーションのデータ構造	
	struct AnimationData
	{
		int handle = -1;			/// アニメーションのハンドル
		float totalTime = -1.0f;	/// アニメーションの総再生時間
	};

public:

	/// @brief アニメーション再生のパラメーター構造体
	struct PlayParams
	{
		int loopCount = 0;		/// ループ回数(0:無限ループ、1:ループ無し)
		float playSpeed = 1.0f;	/// 再生速度
		float blendTime = 0.3f;	/// ブレンド時間
		float startTime = 0.0f;	/// 再生開始時間
	};

	virtual ~DxLibAnimationComponent()
	{
		// 自身が管理するすべてのアニメーションハンドルを解放
		for(auto const& [name, data] : m_animations)
		{
			// ハンドルが有効な場合は解放
			if(data.handle != -1) { MV1DeleteModel(data.handle); }
		}
	}

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	virtual bool Initialize(TOwner& owner) override
	{
		// コンポーネントの所有者を設定する
		IComponent<TOwner>::Initialize(owner);

		// モデルのハンドルを取得して保存
		m_modelHandle = owner.GetModelHandle();

		// ハンドルが有効かどうか
		return m_modelHandle != -1;
	}

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(TOwner& owner, const GameContext& gameContext) override
	{
		if(m_currentAnimAttachIndex == -1) { return; }

		// アニメーションの再生時間を進める
		m_playTime += Anim::FRAME_RATE * m_playSpeed;

		// アニメーションの総再生時間を取得
		float totalTime = m_animations.at(m_currentAnimName).totalTime;
		if(totalTime <= 0.0f) { return; }

		// 無限ループ
		if(m_loopCount == 0)
		{
			// 再生時間が総再生時間を超えたら、再生時間を総再生時間で割った余りにする
			m_playTime = fmod(m_playTime, totalTime);
		}
		// ループ無し
		else if(m_loopCount == 1)
		{
			// 再生時間が総再生時間を超えたら、再生時間を総再生時間にする
			if(m_playTime >= totalTime) { m_playTime = totalTime; }
		}

		// アニメーションの再生時間を設定
		MV1SetAttachAnimTime(m_modelHandle, m_currentAnimAttachIndex, m_playTime);
	}

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief アニメーションを登録する関数
	///
	/// @param animName アニメーションの名前
	/// @param animHandle アニメーションのハンドル
	void RegisterAnimation(const std::string& animName, int animHandle)
	{
		if(animHandle == -1) { return; }

		AnimationData data;
		data.handle				= animHandle;	// アニメーションのハンドルを保存
		m_animations[animName]	= data;			// アニメーションの情報をマップに保存
	}

	/// @brief アニメーションを再生する関数
	///
	/// @param animName 再生するアニメーションの名前
	/// @param params 再生のパラメーター
	void PlayAnimation(const std::string& animName, const PlayParams& params = {})
	{
		// アニメーションが存在しない場合は例外を投げる
		if(m_animations.find(animName) == m_animations.end())
		{
			throw std::runtime_error("アニメーションがなかった: " + animName);
		}

		// アニメーションのインデックスを取得する
		int animIndex = MV1GetAnimIndex(m_modelHandle, animName.c_str());
		if(animIndex == -1)
		{
			throw std::runtime_error("アニメーションが見つからなかった: " + animName);
		}

		// 既に同じアニメーションが同じループ回数で再生されている場合
		if(m_currentAnimName == animName && m_loopCount == params.loopCount)
		{
			// 再生速度だけ更新して終了する
			m_playSpeed = params.playSpeed;

			return;
		}

		// アタッチインデックスが有効な場合
		if(m_currentAnimAttachIndex != -1)
		{
			// 現在のアニメーションをデタッチする
			MV1DetachAnim(m_modelHandle, m_currentAnimAttachIndex);
		}

		auto& data = m_animations.at(animName);

		// アニメーションをアタッチする
		m_currentAnimAttachIndex = MV1AttachAnim(m_modelHandle, animIndex, -1, FALSE);

		// アタッチに失敗した場合は例外を投げる
		if(m_currentAnimAttachIndex == -1)
		{
			throw std::runtime_error("アニメーションのアタッチに失敗: " + animName);
		}

		// アニメーションの総再生時間が保存されていない場合は、アタッチしてから取得する
		if(data.totalTime < 0.0f)
		{
			// アニメーションの総再生時間を取得して保存する
			data.totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentAnimAttachIndex);
		}

		// ブレンド時間が指定されている場合
		if(params.blendTime > 0.0f)
		{
			/*float progress = params.blendTime / data.totalTime;
			float clamp = std::clamp(progress, 0.0f, 1.0f);*/

			// ブレンド時間を設定する
			MV1SetAttachAnimBlendRate(m_modelHandle, m_currentAnimAttachIndex, 1.0f);
		}

		// 状態を更新する
		m_currentAnimName	= animName;			// 現在のアニメーション名を更新
		m_playTime			= params.startTime;	// 再生時間を更新
		m_loopCount			= params.loopCount;	// ループ回数を更新
		m_playSpeed			= params.playSpeed;	// 再生速度を更新
	}

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 現在の再生時間を取得する関数
	///
	/// @return 現在の再生時間
	float GetPlayTime() const { return m_playTime; }

	/// @brief 現在のアニメーションの総再生時間を取得する関数
	///
	/// @return 現在のアニメーションの総再生時間。アニメーションが存在しない場合は0.0f
	float GetCurrentAnimTotalTime() const
	{
		// アニメーションが存在しない場合は0.0fを返す
		if(m_animations.find(m_currentAnimName) == m_animations.end()) { return 0.0f; }

		// アニメーションの総再生時間を返す
		return m_animations.at(m_currentAnimName).totalTime;
	}

	/// @brief アニメーションが終了しているかを取得する関数
	///
	/// @return アニメーションが終了しているならtrue、再生中ならfalse。アニメーションが存在しない場合はtrue
	bool IsAnimationFinished() const
	{
		// ループ再生中は終了しない
		if(m_loopCount == 0) { return false; }

		// アニメーションが存在しない場合はtrueを返す
		if(m_animations.find(m_currentAnimName) == m_animations.end()) { return true; }

		// 現在のアニメーションの総再生時間を取得する
		float totalTime = m_animations.at(m_currentAnimName).totalTime;

		// 再生時間が総再生時間を超えている場合はtrueを返す
		return m_playTime >= totalTime;
	}

private:

	//===========================================================================
	// メンバ関数
	//===========================================================================

	/// アニメーションの情報マップ
	std::unordered_map<std::string, AnimationData> m_animations;

	/// 現在再生中のアニメーション名
	std::string m_currentAnimName = "";

	/// モデルのハンドル
	int m_modelHandle = -1;

	/// ループ回数(0:無限ループ、1:ループ無し)
	int m_loopCount = 0;

	/// 現在再生中のアニメーションのアタッチインデックス
	int m_currentAnimAttachIndex = -1;

	/// 再生時間
	float m_playTime = 0.0f;

	/// 再生速度
	float m_playSpeed = 1.0f;

};