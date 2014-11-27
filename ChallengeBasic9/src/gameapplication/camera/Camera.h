#pragma once
#include "../scene/Scene.h"
#include "../object/Object.h"
class CCamera{
public:

	//�@�C���X�^���X���擾
	static CCamera& GetInstance(){
		static CCamera instance;
		return instance;
	}

	//�@�J�����̏���Ɖ�����ݒ�
	void operator()(const Vec2f& pos,const Vec2f& area_infimum, const Vec2f& area_supre_mum){
		m_pos = pos;
		m_area_infimum = area_infimum - Vec2f(CScene::WIDTH / 2, CScene::HEIGHT / 2);
		m_area_supremum = area_supre_mum + Vec2f(CScene::WIDTH / 2, CScene::HEIGHT / 2);
	}

	//�@�X�V
	void Update(){
		m_pos.x() = std::max(m_pos.x(), m_area_supremum.x());
		m_pos.x() = std::min(m_pos.x(), m_area_infimum.x());

		m_pos.y() = std::max(m_pos.y(), m_area_supremum.y());
		m_pos.y() = std::min(m_pos.y(), m_area_infimum.y());
	};

	//�@���W���擾
	Vec2f GetPos()const{ return m_pos; }

	//�@X���W���擾
	float GetPosX()const{ return m_pos.x(); }

	//�@Y���W���擾
	float GetPosY()const{ return m_pos.y(); }

	//�@���΍��W���擾
	Vec2f RelativeCoordinate(Vec2f& value){
		return value - m_pos;
	}

	//�@X�̑��΍��W���擾
	float RelativeCoordinateX(float value){
		return value - m_pos.x();
	}

	//�@Y�̑��΍��W���擾
	float RelativeCoordinateY(float value){
		return value - m_pos.y();
	}

private:
	CCamera();
	Vec2f m_pos;					//�@�ʒu
	Vec2f m_area_infimum;			//�@infimum����
	Vec2f m_area_supremum;			//�@supremum���
};

