#pragma once
#include "../Scene.h"
#include "../../utility/Font.h"

enum point_u
{
	start,
	lanking,
	explain
};

class Menu : public CScene{
public:
	Menu(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();

	//　キー操作
	void Key_control_u();

	// 初期化
	void flush_initialize();

	//　現在のカーソル位置
	int cursor_point;

	//　点滅
	float
		flush_start,
		flush_lanking,
		flush_explain,

		flush_,
		flush_plus;

private:
	std::unique_ptr<Font>m_font;
};



