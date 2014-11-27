#include "Menu.h"


Menu::Menu(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
m_font(std::make_unique<Font>(60))
{
	m_change_scene = Type::MENU;
	cursor_point = 1;
	flush_ = 0;
	flush_start = 1;
	flush_lanking = 1;
	flush_explain = 1;
	m_res.GetBGM(BGM::MENU)->looping(true);
	m_res.GetBGM(BGM::MENU)->gain(2.0f);
	m_res.GetBGM(BGM::MENU)->play();
	flush_plus = 0.05;
	//m_res.GetBGM(BGM::MENU)->looping(true);
	//m_res.GetBGM(BGM::MENU)->play();
}

//　更新
CScene::Type Menu::Update(){
	Key_control_u();

	flush_ += flush_plus;

	if (m_app_env->isPushKey(GLFW_KEY_ENTER) && cursor_point == point_u::start){
		//m_res.GetBGM(BGM::MENU)->stop();
		m_change_scene = Type::STAGE;
		m_res.GetBGM(BGM::MENU)->stop();
		m_res.GetSE(SE::MENU_SE)->play();
	}

	if (m_app_env->isPushKey(GLFW_KEY_ENTER) && cursor_point == point_u::lanking){
		//m_res.GetBGM(BGM::MENU)->stop();
		m_change_scene = Type::RANKING;
		m_res.GetBGM(BGM::MENU)->stop();
		m_res.GetSE(SE::MENU_SE)->play();
	}

	if (m_app_env->isPushKey(GLFW_KEY_ENTER) && cursor_point == point_u::explain){
		//m_res.GetBGM(BGM::MENU)->stop();
		m_change_scene = Type::RULE;
		m_res.GetBGM(BGM::MENU)->stop();
		m_res.GetSE(SE::MENU_SE)->play();
	}
	return m_change_scene;
}

void Menu::Draw(){
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 1024, 1024, m_res.GetBG(BG::TITLE), Color(1, 1, 1));

	m_font->DrawCenter(L"始める", 0, 150, Color(1, 1, 1, flush_start));
	m_font->DrawCenter(L"ランキング", 0, 0, Color(1, 1, 1, flush_lanking));
	m_font->DrawCenter(L"遊び方", 0, -150, Color(1, 1, 1, flush_explain));
}

void Menu::Key_control_u()
{
	if (m_app_env->isPushKey(GLFW_KEY_UP) && cursor_point > point_u::start)
	{
		flush_initialize();
		cursor_point--;
	}
	if (m_app_env->isPushKey(GLFW_KEY_DOWN) && cursor_point < point_u::explain)
	{
		flush_initialize();
		cursor_point++;
	}

	switch (cursor_point)
	{
	case point_u::start:
		flush_initialize();
		flush_start = std::abs(std::sin(flush_));
		break;

	case point_u::lanking:
		flush_initialize();
		flush_lanking = std::abs(std::sin(flush_));
		break;

	case point_u::explain:
		flush_initialize();
		flush_explain = std::abs(std::sin(flush_));
		break;
	}

}

void Menu::flush_initialize()
{
	flush_start = 1;
	flush_lanking = 1;
	flush_explain = 1;

	if (flush_ >= flush_plus * 60)
		flush_ = 0;
}