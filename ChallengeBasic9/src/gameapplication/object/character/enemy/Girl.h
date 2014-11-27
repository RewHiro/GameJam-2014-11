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
		distance,//       プレイヤーとの距離
		now_move_speed,// 現在の移動速度
		move_speed;//     設定速度

	int
		now_type;//       現在の行動タイプ

	float
		difference_xy;//  distance.x()軸とdistance.y()軸の差

	// 敵との距離の計算とそれに合わせたx軸y軸の移動速度
	void distance_check(Vec2f& player);

	// 追尾移動
	void chase(Vec2f& player);

	// 行動タイプ
	void type(Vec2f& player);

	int m_hp;

	void Death();

	Color m_color;

	void SwitchHP();

	float random_count;
	bool swich_move;

	float distace;

	void Chase();

	// ランダム移動
	void random_move();
	CRandom& m_random;

	Vec2f m_vec;
	std::array<int, 3>m_is;
	Texture m_anime;
};

