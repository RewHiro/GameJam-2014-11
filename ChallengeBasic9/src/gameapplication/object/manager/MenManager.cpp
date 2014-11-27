#include "MenManager.h"

void CMenManager::Update(){
	Create();
	CObjectManager::Update();
}

void CMenManager::Create(){
	for (auto& count : m_create_count){
		count++;
	}
	if (m_create_count[0] == 250){
		Regist(L"����", m_factory.Getobject(CMenFactory::Type::UPPERLEFT));
	}
	if (m_create_count[1] == 250){
		Regist(L"�E��", m_factory.Getobject(CMenFactory::Type::UPPERRIGHT));
	}
	if (m_create_count[2] == 250){
		Regist(L"�E��", m_factory.Getobject(CMenFactory::Type::LOWERRIGHT));

	}
	if (m_create_count[3] == 250){
		Regist(L"����", m_factory.Getobject(CMenFactory::Type::LOWERLEFT));

	}

}