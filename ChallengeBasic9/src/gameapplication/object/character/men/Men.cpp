#include "Men.h"
#include "../../../utility/CRandom.h"
#include "../../../scene/Scene.h"
#include "../../manager/ItemManager.h"
#include "../../item/heart/Heart.h"

CMen::CMen(Type type):
m_type(type),
m_count(0),
m_random(CRandom::GetInstance())
{
	m_kind = static_cast<Kind>(m_random.Uniform(0, 1));
	Vec2f pos;
	switch (m_type){
	case Type::UPPERLEFT:
		pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2+64), static_cast<float>(CScene::HEIGHT / 2));
		m_anime = m_res.GetMen(CResource::Men::UPPER_LEFT);

		break;
	case Type::UPPERRIGHT:
		pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 +700), static_cast<float>(CScene::HEIGHT / 2 - 64 - 30));
		m_anime = m_res.GetMen(CResource::Men::UPPER_RIGHT);

		break;
	case Type::LOWERRIGHT:
		pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 700), static_cast<float>(-CScene::HEIGHT / 2 + 32));
		m_anime = m_res.GetMen(CResource::Men::LOWER_RIGHT);

		break;
	case Type::LOWERLEFT:
		pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 64), static_cast<float>(-CScene::HEIGHT / 2));
		m_anime = m_res.GetMen(CResource::Men::LOWER_LEFT);

		break;
	}
	m_model.Position(pos);
}

void CMen::Update(){
	Create();

	Move();
	Reset();
}

void CMen::Draw(){
	if (!m_is_active)return;

		drawTextureBox(m_model.GetPosX(), m_model.GetPosY(), 80, 80, 0, 0, 128, 128, m_anime, Color(1, 1, 1));
}

void CMen::Create(){
	m_count++;
	switch (m_kind){
	case Kind::GOOD:
		if (m_count == 60){
			m_is_shot = true;
		}
		else if (m_count == 61){
			m_is_shot = false;
		}
		else if (m_count == 120){
			m_is_back = true;
		}
		break;
	case Kind::BAD:
		if (m_count == 60){
			m_is_poison_shot = true;
		}
		else if (m_count == 61){
			m_is_poison_shot = false;
		}
		else if (m_count == 120){
			m_is_back = true;
		}
		break;
	}
}

void CMen::Reset(){
	if (m_is_active)return;
	reset_count++;
	if (reset_count == 400){
		m_is_back = false;
		m_is_shot = false;
		m_is_poison_shot = false;
		m_count = 0;
		m_kind = static_cast<Kind>(m_random.Uniform(0, 1));
		m_is_active = true;
	}
	
}

void CMen::Move(){
	if (!m_is_active)return;
	if (!m_is_back){
		switch (m_type){
		case Type::UPPERLEFT:
			m_model.Translate(0, -5);
			m_model.PositionY(std::max(m_model.GetPosY(), static_cast<float>(CScene::HEIGHT / 2 - 128)));
			break;
		case Type::UPPERRIGHT:
			m_model.Translate(0, -5);
			m_model.PositionY(std::max(m_model.GetPosY(), static_cast<float>(CScene::HEIGHT / 2 - 128)));
			break;
		case Type::LOWERRIGHT:
			m_model.Translate(0, 5);
			m_model.PositionY(std::min(m_model.GetPosY(), static_cast<float>(-CScene::HEIGHT / 2 + 45)));
			break;
		case Type::LOWERLEFT:
			m_model.Translate(0, 5);
			m_model.PositionY(std::min(m_model.GetPosY(), static_cast<float>(-CScene::HEIGHT / 2 + 45)));
			break;
		}
	}
	else {
		Vec2f pos;
		switch (m_type){
		case Type::UPPERLEFT:
			m_model.Translate(0, 5);
			if (m_model.GetPosY() > CScene::HEIGHT / 2+128){
				pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 64), static_cast<float>(CScene::HEIGHT / 2));
				m_model.Position(pos);
				m_is_active = false;
				reset_count = m_random.Uniform(0, 250);
			}
			break;
		case Type::UPPERRIGHT:
			m_model.Translate(0, 5);
			if (m_model.GetPosY() > CScene::HEIGHT / 2+128){
				pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 700), static_cast<float>(CScene::HEIGHT / 2 - 64 - 30));
				m_model.Position(pos);
				m_is_active = false;
				reset_count = m_random.Uniform(0, 250);
			}
			break;
		case Type::LOWERRIGHT:
			m_model.Translate(0, -5);
			if (m_model.GetPosY() < -CScene::HEIGHT / 2-128){
				pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 700), static_cast<float>(-CScene::HEIGHT / 2 + 32));
				m_model.Position(pos);
				m_is_active = false;
				reset_count = m_random.Uniform(0, 250);
			}
			break;
		case Type::LOWERLEFT:
			m_model.Translate(0, -5);
			if (m_model.GetPosY() < -CScene::HEIGHT / 2-128){
				pos = Vec2f(static_cast<float>(-CScene::WIDTH / 2 + 64), static_cast<float>(-CScene::HEIGHT / 2));
				m_model.Position(pos);
				m_is_active = false;
				reset_count = m_random.Uniform(0, 250);
			}
			break;
		}



	}
}