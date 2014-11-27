#include "Title.h"
#include "../SceneManager.h"
#include "../../../lib/graph.hpp"


CTitle::CTitle(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
m_font(std::make_unique<Font>(60))
{

	y_ = -CScene::HEIGHT / 2 + 64 * 2;
	y_plus = 0;

	m_change_scene = Type::TITLE;
	m_res.GetBGM(BGM::TITLE)->looping(false);
	m_res.GetBGM(BGM::TITLE)->play();
}

//　更新
CScene::Type CTitle::Update(){
	Round_trip_y();
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_res.GetBGM(BGM::TITLE)->stop();
		m_change_scene = Type::MENU;
	}
	return m_change_scene;
}

//　描画
void CTitle::Draw(){
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2,
		CScene::WIDTH, CScene::HEIGHT,
		0, 0,
		1000, 700,
		m_res.GetBG(BG::TITLE_2),
		Color(1, 1, 1));

	drawTextureBox(-CScene::WIDTH / 2 + 512 / 2, y_,
		512, 64,
		0, 0,
		512, 64,
		m_res.GetBG(BG::TITLE_STRING),
		Color(1, 1, 1));
	//m_font->DrawCenter(L"モテ食い(仮)",0, 0, Color(1, 1, 1),3);
}

// 動き
void CTitle::Round_trip_y()
{
	y_ += std::cos(y_plus);

	y_plus += 0.1;

	if (y_plus == 360)
		y_plus = 0;
}
