#pragma once
#include "../Scene.h"
#include "../../utility/disp_number.hpp"
class CRanking : public CScene{
public:
	CRanking(std::shared_ptr<AppEnv>app_env);
	//　更新
	Type Update();

	//　描画
	void Draw();

	Texture rank;
	Texture ranking;
	Texture result;

	DispNumber num;
	int i;

	bool update;
	int time[3];
	int temp_time;
	int rank_;

	void bg_switch(const bool&);
	void disp_ranking();
	void disp_result(const int&);
	int get_rank();

public:

	void data_update(const int);

	void data_load();
	void data_save();

	void draw(const bool, int = 0);
	int count;
	std::array<bool, 3>m_is;
};

