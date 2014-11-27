#include "ItemManager.h"
#include "../character/men/Men.h"

void CItemManager::Update(){
	Create();
	CObjectManager::Update();
}

void CItemManager::Create(){
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::MEN).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::MEN).End(); it++){
		if (m_info.GetInfo(CObjectInfoManager::Type::MEN).DynamicCast<CMen>(it)->isShot()){
			Regist(L"ハート", m_factory.Getobject(CItemFactory::Type::NORMAL, m_info.GetInfo(CObjectInfoManager::Type::MEN).GetPos(it)));
		}
	}
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::MEN).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::MEN).End(); it++){
		if (m_info.GetInfo(CObjectInfoManager::Type::MEN).DynamicCast<CMen>(it)->isPoisonShot()){
			Regist(L"ポイズンハート", m_factory.Getobject(CItemFactory::Type::POISON, m_info.GetInfo(CObjectInfoManager::Type::MEN).GetPos(it)));
		}
	}
}