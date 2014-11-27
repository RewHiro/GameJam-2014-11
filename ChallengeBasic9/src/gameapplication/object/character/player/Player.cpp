#include "Player.h"
#include "../enemy/Enemy.h"
#include "../../../utility/Collision.h"
#include "../../item/heart/Heart.h"
#include "../../item/heart/PoisonHeart.h"
#include "../../../scene/Scene.h"
#include "../../character/enemy/Girl.h"
#include <limits>

CPlayer::CPlayer(std::shared_ptr<AppEnv>app_env) :
m_app_env(app_env),
m_attack_power(0),
m_move(MOVE::FRONT),
time(0),
isShot(false),
index(0),
ui_index(0),
walk_count(0),
texture_pos(Vec2f(512, 512)),
texture_size(Vec2f(-512, -512)),
texture_angle(0),
m_is_damage(false),
m_damage_count(0),
isBigShot(false),
effect_swich(false)
{
	m_model.Position(Vec2f(-100, -200));
	m_hit_model.Position(Vec2f(100, 0));
}

//　更新
void CPlayer::Update(){
	if (!m_is_active)return;
	if (m_app_env.lock()->isPushKey(GLFW_KEY_Z)){
		m_attack_power = 9;
	}
	if (isBigShot){
		effect_swich = false;
	}
	Move();
	Hit();
	WalkAnime();
	Damage();
	(m_attack_power != 10) ? Attack() : Special();
	ShotMove();
	ShotRemove();
}

//　描画
void CPlayer::Draw(){
	if (!m_is_active)return;
	if (!m_is_damage){
		drawTextureBox(m_model.GetPosX(), m_model.GetPosY(), 128, 128, texture_pos.x(), texture_pos.y(), texture_size.x(), texture_size.y(), m_res.GetPlayer(index), Color(1, 1, 1), texture_angle, Vec2f(1, 1), Vec2f(64, 64));
	}
	else {
		drawTextureBox(m_model.GetPosX(), m_model.GetPosY(), 128, 128, texture_pos.x(), texture_pos.y(), texture_size.x(), texture_size.y(), m_res.GetPlayerDamage(index), Color(1, 1, 1), texture_angle, Vec2f(1, 1), Vec2f(64, 64));
	}
	//drawCircle(m_model.GetPosX(), m_model.GetPosY(), 32, 32, 20, 2, Color(1, 0, 0));
	// 攻撃力ゲージ
	for (int i = 0; i <= m_attack_power; ++i) {
		gauge_color = (i != 10) ? set_color(i) : Color(1, 0, 0);
		drawFillBox(328, -300, 100, 35 * i, gauge_color);
	}
	drawTextureBox(310, -280, 128, 128, 0, 0, 128, 128, m_res.GetPlayerUI(ui_index), Color(1, 1, 1));


	// ショット
	if (isShot || isBigShot) {
		drawCircle(shot_pos.x(), shot_pos.y(), shot_size.x(), shot_size.y(), 20,5, Color(0, 1, 1));
	}
	if (isShot){
		drawTextureBox(shot_pos.x(), shot_pos.y(), shot_size.x(), shot_size.y(), 0, 0, 64, 64, m_res.GetShot(CResource::Shot::NORMAL), Color(1, 1, 1),0,Vec2f(2,2),Vec2f(shot_size.x()/2,shot_size.y()/2));
	}
	else if (isBigShot){
		drawTextureBox(shot_pos.x(), shot_pos.y(), shot_size.x(), shot_size.y(), 0, 0, 128, 128, m_res.GetShot(CResource::Shot::SPECIAL), Color(1, 1, 1), 0, Vec2f(2, 2), Vec2f(shot_size.x() / 2, shot_size.y() / 2));
		drawTextureBox(shot_pos.x(), shot_pos.y(), shot_size.x(), shot_size.y(), 0, 0, 128, 128, m_res.GetShot(CResource::Shot::STRING), Color(1, 1, 1), 0, Vec2f(2, 2), Vec2f(shot_size.x() / 2, shot_size.y() / 2));
	}

	// ショットの方向
	if (m_attack_power == 10) {
		(attack_d % 2)
			? drawFillCircle(m_model.GetPosX(), m_model.GetPosY() + 50 * (2 - attack_d), 10, 10, 20, Color(1, 0, 0))
			: drawFillCircle(m_model.GetPosX() + 50 * (attack_d - 1), m_model.GetPosY(), 10, 10, 20, Color(1, 0, 0));
		if (attack_d % 2){
			m_res.GetSE(SE::YA)->play();
		}
	}
}

// 攻撃
void CPlayer::Attack() {
	//debug

	if (!isShot && m_attack_power && m_app_env.lock()->isPushKey(GLFW_KEY_ENTER)) {
		shot_pos = m_model.GetPos();
		attack_d = int(m_move);
		isShot = true;
		m_res.GetSE(SE::NORMAL_ATTACK)->play();
		--m_attack_power;
		shot_size = Vec2f(32, 32);
	}
}

// 必殺技
void CPlayer::Special() {
	if (!isBigShot) {
		Direction();

		if (m_app_env.lock()->isPushKey(GLFW_KEY_ENTER)) {
			shot_pos = m_model.GetPos();
			m_res.GetSE(SE::SPECIAL)->play();
			isBigShot = true;
			effect_swich = true;
			shot_size = Vec2f(64, 64);
			m_attack_power = 0;
		}
	}
}

// 攻撃方向決定
void CPlayer::Direction() {
	++time;
	if (time >= 120) { time = 0; }

	switch (time / 30) {
	case /*MOVE::FRONT*/ 1:
		attack_d = int(MOVE::FRONT);
		break;

	case /*MOVE::BACK*/  3:
		attack_d = int(MOVE::BACK);
		break;

	case /*MOVE::LEFT*/  0:
		attack_d = int(MOVE::LEFT);
		break;

	case /*MOVE::RIGHT*/ 2:
		attack_d = int(MOVE::RIGHT);
		break;

	default:;   // 何もしない
	}
}

// ショット移動
void CPlayer::ShotMove() {
	if (isShot || isBigShot) {
		switch (attack_d) {
		case 1: shot_pos.y() += 10; break;  // MOVE::FRONT
		case 3: shot_pos.y() -= 10; break;  // MOVE::BACK
		case 0: shot_pos.x() -= 10; break;  // MOVE::LEFT
		case 2: shot_pos.x() += 10; break;  // MOVE::RIGHT
		default:;   // 何もしない
		}
	}
}

//　移動処理
void CPlayer::Move(){
	index = (walk_count / 10) % 2;
	if (m_app_env.lock()->isPressKey(GLFW_KEY_D)){
		m_model.Translate(5, 0);
		m_move = MOVE::RIGHT;
		walk_count++;
	}
	else if (m_app_env.lock()->isPressKey(GLFW_KEY_A)){
		m_model.Translate(-5, 0);
		m_move = MOVE::LEFT;
		walk_count++;
	}
	if (m_app_env.lock()->isPressKey(GLFW_KEY_S)){
		m_model.Translate(0, -5);
		m_move = MOVE::BACK;
		walk_count++;
	}
	else if (m_app_env.lock()->isPressKey(GLFW_KEY_W)){
		m_model.Translate(0, 5);
		m_move = MOVE::FRONT;
		walk_count++;
	}
}

void CPlayer::Hit(){
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ITEM).Begin(L"ハート"); it != m_info.GetInfo(CObjectInfoManager::Type::ITEM).End(L"ハート"); it++){
		if (Collision::CircleAndCircle(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::ITEM).GetHitPos(it), 32, 15)){
			m_attack_power++;
			m_res.GetSE(SE::HEART_HIT)->play();
			m_info.GetInfo(CObjectInfoManager::Type::ITEM).DynamicCast<CHeart>(it)->TransformOfDeath();
			if (m_attack_power > 10){
				m_attack_power = 10;
			}
		}
	}

	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ITEM).Begin(L"ポイズンハート"); it != m_info.GetInfo(CObjectInfoManager::Type::ITEM).End(L"ポイズンハート"); it++){
		if (Collision::CircleAndCircle(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::ITEM).GetHitPos(it), 32, 15)){
			m_attack_power--;
			m_is_damage = true;
			m_res.GetSE(SE::POISON_HEART_HIT)->play();
			m_info.GetInfo(CObjectInfoManager::Type::ITEM).DynamicCast<CPoisonHeart>(it)->TransformOfDeath();
			if (m_attack_power < 0){
				m_attack_power = 0;
			}
		}
	}
	if (isShot){
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
			if (Collision::CircleAndCircle(shot_pos, m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetHitPos(it), shot_size.x(), 32)){
				isShot = false;
				m_info.GetInfo(CObjectInfoManager::Type::ENMEY).DynamicCast<CGirl>(it)->TransFormHP(1);
			}
		}
	}

	if (isBigShot){
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
			if (Collision::CircleAndCircle(shot_pos, m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetHitPos(it), shot_size.x(), 32)){
				isBigShot = false;
				m_info.GetInfo(CObjectInfoManager::Type::ENMEY).DynamicCast<CGirl>(it)->TransFormHP(5);
			}
		}
	}


	if (!m_is_damage){
		for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
			if (Collision::CircleAndCircle(m_model.GetPos(), m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetHitPos(it), 32, 32)){
				m_attack_power -= 3;
				m_is_damage = true;
				m_res.GetSE(SE::BOS_HIT)->play();
				if (m_attack_power < 0){
					m_attack_power = 0;
				}
			}
		}
	}
}

void CPlayer::WalkAnime(){
	switch (m_move)
	{
	case MOVE::FRONT:
		texture_pos = Vec2f(512, 512);
		texture_size = Vec2f(-512, -512);
		texture_angle = 0;
		break;
	case MOVE::BACK:
		texture_pos = Vec2f(0, 0);
		texture_size = Vec2f(512, 512);
		texture_angle = 0;
		break;
	case MOVE::RIGHT:
		texture_pos = Vec2f(0, 0);
		texture_size = Vec2f(512, 512);
		texture_angle = M_PI / 2;
		break;
	case MOVE::LEFT:
		texture_pos = Vec2f(0, 0);
		texture_size = Vec2f(512, 512);
		texture_angle = -M_PI / 2;
		break;
	}
	if (m_attack_power < 4){
		ui_index = 0;
	}
	else if (m_attack_power < 7){
		ui_index = 1;
	}
	else{
		ui_index = 2;
	}
}

Color CPlayer::set_color(int& i){
	if (i < 4) { return Color(0, 0, 1); }
	if (i < 7) { return Color(0, 1, 0); }
	return Color(1, 1, 0);
}

void CPlayer::Damage(){
	if (!m_is_damage)return;
	m_damage_count++;
	if (m_damage_count == 180){
		m_is_damage = false;
		m_damage_count = 0;
	}
}

void CPlayer::ShotRemove(){

	if ((-CScene::WIDTH / 2 + 40 > shot_pos.x()) || (shot_pos.x() > -CScene::WIDTH / 2 + 40 + 700)){
		isShot = false;
		isBigShot = false;
	}
	if ((-CScene::HEIGHT / 2 + 40 > shot_pos.y()) || (shot_pos.y() > -CScene::HEIGHT / 2 + 40 + 600)){
		isShot = false;
		isBigShot = false;
	}
}