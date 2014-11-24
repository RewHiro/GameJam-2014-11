#include "Stage.h"
#include "../SceneManager.h"
#include "../../object/character/player/Player.h"
#include "../../object/character/enemy/Enemy.h"
#include "../../object/manager/PlayerManager.h"
#include "../../object/manager/EnemyManager.h"


CStage::CStage(std::shared_ptr<AppEnv>app_env) :
CScene(app_env)
{
	m_change_scene = Type::STAGE;
	m_res.GetBGM(BGM::STAGE)->looping(true);
	m_res.GetBGM(BGM::STAGE)->play();
	m_obj_task.Regist(3, std::make_unique<CPlayerManager>(app_env));
	m_obj_task.Regist(2, std::make_unique<CEnemyManager>());

}

//　更新
CScene::Type CStage::Update(){
	m_obj_task.Update();
	if (m_app_env->isPushKey(GLFW_KEY_ENTER)){
		m_res.GetBGM(BGM::STAGE)->stop();
		m_info.Crear();
		m_change_scene = Type::TITLE;
	}
	return m_change_scene;
}

//　描画
void CStage::Draw(){

	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 1024, 512, m_res.GetBG(BG::STAGE), Color(1, 1, 1));
	m_obj_task.Draw();
}
