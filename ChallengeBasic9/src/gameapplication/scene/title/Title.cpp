#include "Title.h"
#include "../SceneManager.h"
#include "../../../lib/graph.hpp"


CTitle::CTitle(std::shared_ptr<AppEnv>app_env) :
CScene(app_env)
{
	m_change_scene = Type::TITLE;
	m_res.GetBGM(BGM::TITLE)->looping(true);
	m_res.GetBGM(BGM::TITLE)->play();
}

//　更新
CScene::Type CTitle::Update(){
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_res.GetBGM(BGM::TITLE)->stop();
		m_change_scene = Type::STAGE;
	}
	return m_change_scene;
}

//　描画
void CTitle::Draw(){
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 1024, 512, m_res.GetBG(BG::TITLE), Color(1, 1, 1));
	drawFillBox(0, 0, 20, 20, Color(1, 1, 0));
}

