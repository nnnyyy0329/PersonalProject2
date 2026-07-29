#pragma once

class		Character;		/// キャラクタークラス
struct		AttackMoveData;	/// 攻撃移動データ構造体
enum class	AttackPhase;	/// 攻撃のフェーズを表す列挙型

using C		= Character;		/// キャラクタークラスのエイリアス
using AMD	= AttackMoveData;	/// 攻撃移動データ構造体のエイリアス
using AP	= AttackPhase;		/// 攻撃のフェーズを表す列挙型のエイリアス

/// @brief 攻撃時に前方へ踏み込む処理を行うクラス
class AttackLunge
{
public:

	~AttackLunge() = default;

	//======================================================================
	// 基本関数
	//======================================================================

	/// @brief 更新関数
	///
	/// @param character キャラクタークラスの参照
	/// @param attackMoveData 攻撃移動データ構造体の参照
	/// @param currentPhase 現在の攻撃のフェーズを表す列挙型
	/// @param stateTime 攻撃のフェーズの経過時間
	void Update(C& character, const AMD& attackMoveData, AP currentPhase, float stateTime);

	//======================================================================
	// 内部関数
	//======================================================================

	/// @brief 攻撃時に前方へ踏み込む処理を行う関数
	///
	/// @param character キャラクタークラスの参照
	/// @param attackMoveData 攻撃移動データ構造体の参照
	void MoveLunge(C& character, const AMD& attackMoveData);

};

