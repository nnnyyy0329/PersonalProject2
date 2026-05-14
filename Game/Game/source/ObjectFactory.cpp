#include "ObjectFactory.h"
#include "Player.h"

std::unique_ptr<ObjectLogic> ObjectFactory::CreateObject(OBJECT_TYPE type)
{
	// 生成されたオブジェクトのロジッククラスのユニークポインタ
	std::unique_ptr<ObjectLogic> obj;

	// オブジェクトの種類に応じて生成
	switch (type)
	{
		case OBJECT_TYPE::PLAYER:	// プレイヤーオブジェクトの生成
		{
			obj = std::make_unique<Player>();
			break;
		}

		case OBJECT_TYPE::ENEMY:	// 敵オブジェクトの生成
		{
			break;
		}
			
		default:
			break;
	}

	return obj;
}