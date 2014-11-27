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
		Regist(L"女の子", m_factory.Getobject(CEnemyFactory::Type::GIRL));
		m_info_manager(InfoType::ENMEY).GetInfo(InfoType::ENMEY).Regist(m_obj_regist);
	}
private:
	CEnemyFactory m_factory;
};

