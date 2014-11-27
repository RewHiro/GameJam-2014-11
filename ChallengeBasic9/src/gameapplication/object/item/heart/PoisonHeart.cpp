#include "PoisonHeart.h"
#include "../../../utility/Math.h"
#include "../../../scene/Scene.h"

CPoisonHeart::CPoisonHeart(Vec2f& pos){
	m_model.Position(pos);
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
		distace = Math::Get2Distancef(pos, m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetPos(it));
	}
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
		m_vec.x() = -((pos.x() - m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetPosX(it)) / distace * 1);
		m_vec.y() = -((pos.y() - m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetPosY(it)) / distace * 1);
	}
	m_hit_model.Position(pos);
}

void CPoisonHeart::Update(){
	Move();
	m_hit_model.Position(m_model.GetPosX() + 32, m_model.GetPosY() + 32);
	Death();
}

void CPoisonHeart::Draw(){
	if (!m_is_active)return;
	drawTextureBox(m_model.GetPosX(), m_model.GetPosY(), 64, 64, 0, 0, 128, 128, m_res.GetItem(CResource::Item::NORMAL), Color(1, 1, 1));
	//drawCircle(m_hit_model.GetPosX(), m_hit_model.GetPosY(), 15, 15, 30, 5, color256(255, 255, 0));
}

void CPoisonHeart::Move(){
	m_model.Translate(m_vec);
	if ((-CScene::WIDTH / 2 + 40 > m_model.GetPosX()) || (m_model.GetPosX() > -CScene::WIDTH / 2 + 40 + 700)){
		m_is_active = false;
	}
	if ((-CScene::HEIGHT / 2 + 40 > m_model.GetPosY()) || (m_model.GetPosY() > -CScene::HEIGHT / 2 + 40 + 600)){
		m_is_active = false;
	}
}

void CPoisonHeart::Death(){
	if (m_is_active)return;
	m_is_delete = true;
}