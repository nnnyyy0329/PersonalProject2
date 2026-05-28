#pragma once

/// @brief キャラクターのコンポーネントを管理するクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class IComponent
{
public:

	virtual ~IComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	/// 
	/// @param owner 初期化処理を行うキャラクター
	///
	/// @return 成功しているならtrue、失敗しているならfalse
	virtual bool Initialize(TOwner& owner) { return true; }

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	virtual void Update(TOwner& owner) {};
};

