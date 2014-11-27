#pragma once
#include "Enemy.h"
#include "../../../utility/CRandom.h"
#include <array>

enum character_size
{
	girl = 150,
	player = 70
};

enum active_type
{
	not_move,
	chase,
	random
};


class CGirl : public CEnemy{
public:
	CGirl();

	void Update();

	void Draw();

	void TransFormHP(int value){
		m_hp -= value;
	}

private:
	Vec2f
		distance,//       �v���C���[�Ƃ̋���
		now_move_speed,// ���݂̈ړ����x
		move_speed;//     �ݒ葬�x

	int
		now_type;//       ���݂̍s���^�C�v

	float
		difference_xy;//  distance.x()����distance.y()���̍�

	// �G�Ƃ̋����̌v�Z�Ƃ���ɍ��킹��x��y���̈ړ����x
	void distance_check(Vec2f& player);

	// �ǔ��ړ�
	void chase(Vec2f& player);

	// �s���^�C�v
	void type(Vec2f& player);

	int m_hp;

	void Death();

	Color m_color;

	void SwitchHP();

	float random_count;
	bool swich_move;

	float distace;

	void Chase();

	// �����_���ړ�
	void random_move();
	CRandom& m_random;

	Vec2f m_vec;
	std::array<int, 3>m_is;
	Texture m_anime;
};

