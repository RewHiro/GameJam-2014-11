#pragma once
#include "ObjectManager.h"
#include "../regist/ObjectRegist.h"
#include "../factory/EnemyFactory.h"

//========================================
//�v���C���[�Ǘ��N���X
//========================================

class CEnemyManager : public CObjectManager{
public:
	CEnemyManager::CEnemyManager(){
		Regist(L"���̎q", m_factory.Getobject(CEnemyFactory::Type::GIRL));
		m_info_manager(InfoType::ENMEY).GetInfo(InfoType::ENMEY).Regist(m_obj_regist);
	}
private:
	CEnemyFactory m_factory;
};

