#pragma once
#include "../Character.h"
#include "../../info/ObjectInfoManager.h"
#include "../../../utility/Font.h"

class CPlayer : public CCharacter
{
public:
	CPlayer(std::shared_ptr<AppEnv>);

	//　更新
	void Update();

	//　描画
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
	//　移動処理
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



	// 攻撃処理
	Vec2f shot_pos;     // ショット座標
	Vec2f shot_size;
	bool isShot;        // ショット発射フラグ
	bool isBigShot;        // ショット発射フラグ

	int time;
	int attack_d;       // 通常攻撃の方向
	void Attack();      // 攻撃
	void Special();     // 必殺技
	void Direction();   // 攻撃方向決定
	void ShotMove();    // ショット移動
	void ShotRemove();

	bool effect_swich;
};

