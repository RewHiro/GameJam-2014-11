#pragma once
#include "../Character.h"
#include "../../info/ObjectInfoManager.h"
#include "../../../utility/Font.h"

class CPlayer : public CCharacter
{
public:
	CPlayer(std::shared_ptr<AppEnv>);

	//�@�X�V
	void Update();

	//�@�`��
	void Draw();

	int GetAttackPower(){ return m_attack_power; }

	enum class MOVE{
		LEFT,
		FRONT,
		RIGHT,
		BACK
	};

	bool GetAnime(){
		return effect_swich;
	}

private:
	std::weak_ptr<AppEnv>m_app_env;
	CObjectInfoManager m_info;
	//�@�ړ�����
	void Move();
	int m_attack_power;
	void Hit();
	MOVE m_move;
	int index;
	int ui_index;
	int walk_count;
	void WalkAnime();
	Vec2f texture_pos;
	Vec2f texture_size;
	float texture_angle;
	Color gauge_color;
	Color set_color(int& i);
	bool m_is_damage;
	int m_damage_count;
	void Damage();
	std::unique_ptr<Font>m_font;



	// �U������
	Vec2f shot_pos;     // �V���b�g���W
	Vec2f shot_size;
	bool isShot;        // �V���b�g���˃t���O
	bool isBigShot;        // �V���b�g���˃t���O

	int time;
	int attack_d;       // �ʏ�U���̕���
	void Attack();      // �U��
	void Special();     // �K�E�Z
	void Direction();   // �U����������
	void ShotMove();    // �V���b�g�ړ�
	void ShotRemove();

	bool effect_swich;
};

