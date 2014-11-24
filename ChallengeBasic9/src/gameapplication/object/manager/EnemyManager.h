#pragma once
#include "ObjectManager.h"
#include "../regist/ObjectRegist.h"
#include "../factory/EnemyFactory.h"

//========================================
//プレイヤー管理クラス
//========================================

class CEnemyManager : public CObjectManager{
public:
	CEnemyManager::CEnemyManager(){
		Regist(L"スライム", m_factory.Getobject(CEnemyFactory::Type::SLIME, 10, 20));
		Regist(L"ドラゴン", m_factory.Getobject(CEnemyFactory::Type::DRAGON, 300, 20));
		m_info_manager(InfoType::ENMEY).GetInfo(InfoType::ENMEY).Regist(m_obj_regist);
	}
private:
	CEnemyFactory m_factory;
};

