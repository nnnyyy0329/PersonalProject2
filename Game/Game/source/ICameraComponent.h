#pragma once

/// @brief カメラコンポーネントを管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class ICameraComponent
{
public:

	virtual ~ICameraComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	virtual bool Initialize(TOwner& owner) override{ return true; }

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	virtual void Update(TOwner& owner) = 0;

};