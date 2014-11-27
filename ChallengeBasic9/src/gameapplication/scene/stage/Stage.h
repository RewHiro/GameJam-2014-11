#pragma once
#include "../Scene.h"
#include "../../resource/Resource.h"
#include "../../task/ObjectTask.h"
#include "../../utility/Font.h"
#include <vector>

//========================================
//ステージクラス
//========================================
class CStage : public CScene{
public:
	CStage(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();
private:
	CObjectTask m_obj_task;
	CObjectInfoManager m_info;
	int m_time_count;
	void Time();
	std::unique_ptr<Font>m_time_num;
	std::vector<std::unique_ptr<Font>>m_string;
	bool isStart = false;
	Vec2f string_pos;
	void Start();
	void Ready();

	std::array<int, 3>m_now_stage;

	bool isRead;
	static int num;
	// カラー
	float
		R_,
		G_,
		B_,

		Fade_,
		Alpha_,

		font_x,
		font_y,

		ready_count;

	unsigned int
		font_size;

	Texture game_over;
	void GameOver();

	void TimeDraw();
	Texture sand_grass;
	Texture time_start;
	Texture time_end;
	Texture time1;
	Texture time2;
	Texture time3;
	Texture time4;


	void Cutin();

	bool isAnime = false;

	float cutin_move;
	float cutin_count;
	float cutin_effect_alp;

};