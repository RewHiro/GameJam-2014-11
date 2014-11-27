#pragma once
#include "../Character.h"
#include "../../info/ObjectInfoManager.h"
#include <unordered_map>
#include <string>

class CEnemy : public CCharacter{
public:
	CEnemy();


	//　更新
	void Update();

	//　描画
	void Draw();

protected:
	int m_count;
	CObjectInfoManager m_info;
	Color m_color;
};

