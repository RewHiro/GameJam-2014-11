#pragma once
#include "../Item.h"
#include "../../info/ObjectInfoManager.h"

class CHeart : public CItem{
public:
	CHeart(Vec2f& pos);

	void Update();

	void Draw();

	void TransformOfDeath(){
		m_is_active = false;
		m_is_delete = true;
	}
private:
	void Move();
	float distace;
	CObjectInfoManager m_info;
	Vec2f m_vec;
	void Death();
	void Hit();
};

