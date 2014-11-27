#pragma once
#include "ObjectManager.h"
#include "../regist/ObjectRegist.h"
#include "../factory/ItemFactory.h"

//========================================
//プレイヤー管理クラス
//========================================

class CItemManager : public CObjectManager{
public:
	CItemManager::CItemManager()
	{
		m_info_manager(InfoType::ITEM).GetInfo(InfoType::ITEM).Regist(m_obj_regist);
	}

	void Update();

	void Create();
private:
	CItemFactory m_factory;
	CObjectInfoManager m_info;
};

