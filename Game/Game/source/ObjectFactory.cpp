#include "ObjectFactory.h"
#include "ObjectLogic.h"
#include "Player.h"

void ObjectFactory::RegisterObject(const std::string& name, CreateFunc func)
{
	m_objectCreators[name] = func;
}

std::unique_ptr<ObjectLogic> ObjectFactory::CreateObject(const std::string& name)
{
	// 登録された生成関数を検索
	auto objects = m_objectCreators.find(name);

	// 登録された生成関数が見つかった場合
	if(objects != m_objectCreators.end())
	{
		// 登録された生成関数を呼び出してオブジェクトを生成
		return objects->second();	
	}

	// 登録されていない場合はnullptrを返す
	return nullptr;	
}
