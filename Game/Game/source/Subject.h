#pragma once
#include <vector>

/// @brief オブザーバーパターンの管理クラス
/// 
/// @tparam TObserver オブザーバーの型
template<typename TObserver>
class Subject
{
public:

	virtual ~Subject() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief オブザーバーを追加する関数
	///
	/// @param observer 追加するオブザーバーのポインタ
	void AddObserver(TObserver* observer)
	{
		// 追加されていない場合は追加する
		m_observers.push_back(observer);
	}

	/// @brief オブザーバーを削除する関数
	///
	/// @param observer 削除するオブザーバーのポインタ
	void RemoveObserver(TObserver* observer)
	{
		// オブザーバーのリストから指定されたオブザーバーを検索する
		auto observers = std::find(m_observers.begin(), m_observers.end(), observer);

		// 見つかった場合
		if(observers != m_observers.end())
		{
			// オブザーバーを削除する
			m_observers.erase(observers);
		}
	}

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// オブザーバーのリスト
	std::vector<TObserver*> m_observers;

};