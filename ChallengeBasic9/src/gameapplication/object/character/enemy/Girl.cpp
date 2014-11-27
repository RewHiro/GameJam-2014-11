#include "Girl.h"
#include "../../../utility/Math.h"

#include "../../../scene/Scene.h"

#include <fstream>

CGirl::CGirl() :
m_random(CRandom::GetInstance())
{
	m_model.Position(Vec2f(-100, 0));

	swich_move = m_random.Bernulli(0.5);
	random_count = 0;
	std::ifstream lead("res/clear.txt");
	if (lead){
		lead >> m_is[0];
		lead >> m_is[1];
		lead >> m_is[2];
	}
	
	if (!m_is[0]){
		now_type = 0;
	}

	if (!m_is[1]){
		now_type = 1;
	}
	if (!m_is[2]){
		now_type = 2;
	}

	m_anime = m_res.GetBoss(0);



	m_hp = 15;
	m_color = Color(1, 1, 1);

}


void CGirl::Update(){
	m_hit_model = m_model;

	SwitchHP();
	Vec2f i;
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
		i = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPos(it);
	}

	//m_random.Bernulli(0.4);

	//Vec2f i(-100, 0);

	type(i);
	if (m_hp <= 0)
	{
		m_is_active = false;
	}
	//Chase();

}



void CGirl::Draw(){
	if (!m_is_active)return;
	drawTextureBox(m_model.GetPosX(), m_model.GetPosY(), 128, 128, 0, 0, 128, 128, m_anime, Color(1,1,1), 0, Vec2f(1, 1), Vec2f(64, 64));
	//drawCircle(m_model.GetPosX(), m_model.GetPosY(), 32, 32, 20, 2, Color(1, 0, 0));
}


// プレイヤーとの距離とそれに合わせた移動速度
void CGirl::distance_check(Vec2f& player)
{
	distance.x() = player.x() - m_model.GetPosX();
	distance.y() = player.y() - m_model.GetPosY();

	if (std::abs(distance.x()) >= std::abs(distance.y()))
	{
		now_move_speed.x() = move_speed.x();
		difference_xy = std::abs(distance.x()) - std::abs(distance.y());

		now_move_speed.y() -= difference_xy;
		if (now_move_speed.y() <= 0)
			now_move_speed.y() = 0;
	}
	else if (std::abs(distance.x()) <= std::abs(distance.y()))
	{
		now_move_speed.y() = move_speed.y();
		difference_xy = std::abs(distance.y()) - std::abs(distance.x());

		now_move_speed.x() -= difference_xy;
		if (now_move_speed.x() <= 0)
			now_move_speed.x() = 0;
	}

}

// 追尾移動
void CGirl::chase(Vec2f& player)
{
	distance_check(player);

	if (distance.x() > 0)
		m_model.Translate(now_move_speed.x(), 0);
	else if (distance.x() < 0)
		m_model.Translate(-now_move_speed.x(), 0);

	if (distance.y() < 0)
		m_model.Translate(0, -now_move_speed.y());
	else if (distance.y() > 0)
		m_model.Translate(0, now_move_speed.y());
}

// 行動タイプの取得 (now_type はコンストラクタでいれてますよ)
void CGirl::type(Vec2f& player)
{
	switch (now_type)
	{
	case active_type::not_move:
		break;

	case active_type::chase:
		Chase();
		break;

	case active_type::random:
		random_move();
		break;
	}
}

void CGirl::Chase(){
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
		distace = Math::Get2Distancef(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPos(it));
	}
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
		m_vec.x() = -((m_model.GetPosX() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosX(it)) / distace * 1);
		m_vec.y() = -((m_model.GetPosY() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosY(it)) / distace * 1);
	}
	m_model.Translate(m_vec);

}

void CGirl::random_move()
{

	if (swich_move && random_count < 60)
	{
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
			distace = Math::Get2Distancef(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPos(it));
		}
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){

			m_vec.x() = +((m_model.GetPosX() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosX(it)) / distace * 2);
			m_vec.y() = +((m_model.GetPosY() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosY(it)) / distace * 2);
		}

		if ((-CScene::WIDTH / 2 + 70 > m_model.GetPosX()) || (m_model.GetPosX() > -CScene::WIDTH / 2 + 40 + 700)){
			m_vec.x() = false;
		}
		if ((-CScene::HEIGHT / 2 + 90 > m_model.GetPosY()) || (m_model.GetPosY() > -CScene::HEIGHT / 2 + 40 + 550)){
			m_vec.y() = false;
		}

		m_model.Translate(m_vec);
	}
	else if (!swich_move && random_count < 60)
	{
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
			distace = Math::Get2Distancef(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPos(it));
		}
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
			m_vec.y() = -((m_model.GetPosY() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosY(it)) / distace * 2);
			m_vec.x() = -((m_model.GetPosX() - m_info.GetInfo(CObjectInfoManager::Type::PLAYER).GetPosX(it)) / distace * 2);
		}



		m_model.Translate(m_vec);
	}




	if (random_count < 180)
	{
		random_count++;
	}
	else
	{
		random_count = 0;
		swich_move = m_random.Bernulli(0.35);
	}


}

void CGirl::SwitchHP(){
	if (m_hp <=5 ){
		m_anime = m_res.GetBoss(2);
	}
	else if (m_hp <= 10){
		m_anime = m_res.GetBoss(1);

	}
	else if (m_hp <= 15){

		m_anime = m_res.GetBoss(0);
	}
}