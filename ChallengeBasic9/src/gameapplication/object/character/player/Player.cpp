#include "Player.h"
#include "../enemy/Enemy.h"

CPlayer::CPlayer(std::shared_ptr<AppEnv>app_env):
m_app_env(app_env)
{
	m_model.Position(Vec2f(0, 0));
	m_hit_model.Position(Vec2f(100, 0));
}

//　更新
void CPlayer::Update(){
	if (!m_is_active)return;
	Move();
	for (auto it = m_info.GetInfo(InfoType::ENMEY).Begin(); it != m_info.GetInfo(InfoType::ENMEY).End(); it++){
		Vec2f i = m_info.GetInfo(InfoType::ENMEY).GetPos(it);
	}

}

//　描画
void CPlayer::Draw(){
	if (!m_is_active)return;
	drawFillBox(m_model.GetPosX(), m_model.GetPosY(), 64, 64, Color(1, 0, 0));
}

//　移動処理
void CPlayer::Move(){
	if (m_app_env.lock()->isPressKey(GLFW_KEY_RIGHT)){
		m_model.Translate(5, 0);
	}
	else if (m_app_env.lock()->isPressKey(GLFW_KEY_LEFT)){
		m_model.Translate(-5, 0);
	}
	if (m_app_env.lock()->isPressKey(GLFW_KEY_DOWN)){
		m_model.Translate(0, -5);
	}
	else if (m_app_env.lock()->isPressKey(GLFW_KEY_UP)){
		m_model.Translate(0, 5);
	}
}