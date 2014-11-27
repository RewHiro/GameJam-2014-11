#pragma once
#include "ObjectManager.h"
#include "../regist/ObjectRegist.h"
#include "../factory/MenFactory.h"
#include "../../utility/CRandom.h"
#include <array>

//========================================
//プレイヤー管理クラス
//========================================

class CMenManager : public CObjectManager{
public:
	CMenManager::CMenManager():
	m_random(CRandom::GetInstance())
	{
		for (auto& count : m_create_count){
			count = m_random.Uniform(0,50);
		}
		m_info_manager(InfoType::MEN).GetInfo(InfoType::MEN).Regist(m_obj_regist);
	}

	void Update();

	void Create();
private:
	CMenFactory m_factory;
	std::array<int, 4>m_create_count;
	CRandom& m_random;
};

