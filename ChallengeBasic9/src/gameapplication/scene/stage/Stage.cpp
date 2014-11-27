#include "Stage.h"
#include "../SceneManager.h"
#include "../../object/character/player/Player.h"
#include "../../object/character/enemy/Enemy.h"
#include "../../object/manager/PlayerManager.h"
#include "../../object/manager/EnemyManager.h"
#include "../../object/manager/ItemManager.h"
#include "../../object/manager/MenManager.h"
#include <fstream>


int CStage::num = 0;

CStage::CStage(std::shared_ptr<AppEnv>app_env) :
CScene(app_env),
sand_grass(Texture("res/graph/sand_grass.png")),
game_over(Texture("res/graph/gameover.png")),
time_start(Texture("res/graph/time_start.png")),
time_end(Texture("res/graph/time_end.png")),
time1(Texture("res/graph/time_1.png")),
time2(Texture("res/graph/time_2.png")),
time3(Texture("res/graph/time_3.png")),
time4(Texture("res/graph/time_4.png")),
m_time_count(60 * 60),
m_time_num(std::make_unique<Font>(40))
{
	m_app_env->bgColor(Color(1, 1, 1));
	m_change_scene = Type::STAGE;
	m_res.GetBGM(BGM::STAGE)->looping(true);
	m_res.GetBGM(BGM::STAGE)->play();
	m_obj_task.Regist(1, std::make_unique<CPlayerManager>(app_env));
	m_obj_task.Regist(2, std::make_unique<CEnemyManager>());
	m_obj_task.Regist(4, std::make_unique<CMenManager>());
	m_obj_task.Regist(3, std::make_unique<CItemManager>());
	m_string.emplace_back(std::make_unique<Font>(40, L"ニコモジ"));

	if (num == 0){
		num++;
		std::ofstream read("res/clear.txt");
		if (read){
			for (int i = 0; i < 3; i++){
				read << 0 << std::endl;
			}
		}
	}

	if (num > 0){
		std::ifstream lead("res/clear.txt");
		if (lead){
			for (int i = 0; i < 3; i++){
				lead >> m_now_stage[i];
			}
		}
	}

	font_x = -120;
	font_y = 0;

	R_ = 1;
	G_ = 1;
	B_ = 1;

	Fade_ = 1;
	Alpha_ = 0;

	font_size = 0;

	isStart = false;
	ready_count = 0;


	isAnime = false;
	cutin_move = 0;
	cutin_count = 0;
	cutin_effect_alp = 0.6;
}

//　更新
CScene::Type CStage::Update(){
	Ready();
	Cutin();
	Start();
	return m_change_scene;
}

//　描画
void CStage::Draw(){

	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 993, 700, m_res.GetBG(BG::STAGE_PLAY), Color(1, 1, 1));
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 993, 700, m_res.GetBG(BG::UI), Color(1, 1, 1));


	m_obj_task.Draw();
	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 993, 700, m_res.GetBG(BG::STAGE), Color(1, 1, 1));

	// ゲームオーバーと砂時計の描画
	if (m_time_count <= 0) GameOver();
	TimeDraw();

	//m_time_num->DrawCenter(std::to_wstring(m_time_count / 60), 400, 200, Color(1, 1, 1));

	m_string[0]->TransformOfSize(font_size);
	m_string[0]->DrawCenter(L"Ready", font_x, font_y, Color(R_, G_, B_), 3);



	//-----------
	// カットイン
	if (isAnime)
	{
		if (cutin_count < 70)
		{
			drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, 0, 0, 1000, 700, m_res.GetAnimeCut(CResource::Anime::CHAR), Color(1, 1, 1, 0.9));
			drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT, cutin_move, 0, 1024, 256, m_res.GetAnimeCut(CResource::Anime::BG), Color(1, 1, 1, cutin_effect_alp));
			cutin_count++;
			cutin_move += 20;
			cutin_effect_alp -= 0.01;

		}
		else if(cutin_count == 70){
			isAnime = false;
			cutin_count = 0;
			cutin_move = 0;
			cutin_effect_alp = 0.6;

		}

	}
}

// ゲームオーバー
void CStage::GameOver() {
	if (Fade_ > 0.25f) { Fade_ -= 0.02f; }
	if (Fade_ <= 0.25f && Alpha_ < 1.0f) { Alpha_ += 0.05; }

	drawTextureBox(-CScene::WIDTH / 2, -CScene::HEIGHT / 2, CScene::WIDTH, CScene::HEIGHT,
		0, 0, CScene::WIDTH, CScene::HEIGHT,
		game_over, Color(Fade_ * 2, Fade_ * 2, Fade_ * 2, Alpha_));

	m_string[0]->TransformOfSize(120);
	m_string[0]->DrawCenter(L"GameOver", font_x, font_y + 200, Color(1, 1, 1, Alpha_), 3);

	m_string[0]->TransformOfSize(60);
	m_string[0]->DrawCenter(L"R key to Retry", font_x, font_y + 30, Color(1, 1, 1, Alpha_), 3);

	m_string[0]->TransformOfSize(60);
	m_string[0]->DrawCenter(L"E key to Exit ", font_x, font_y - 50, Color(1, 1, 1, Alpha_), 3);
}

// 砂時計（制限時間）
void CStage::TimeDraw() {

	// 砂時計
	drawTextureBox(-500, -350, 1000, 700,
		0, 0, 1000, 700,
		sand_grass, Color(1, 1, 1));

	// 砂
	switch (1 + m_time_count / 60 / 10) {
	case 7:
	case 6:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time_start, Color(1, 1, 1));
		break;

	case 5:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time1, Color(1, 1, 1));
		break;

	case 4:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time2, Color(1, 1, 1));
		break;

	case 3:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time3, Color(1, 1, 1));
		break;

	case 2:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time4, Color(1, 1, 1));
		break;

	case 1:
		drawTextureBox(-500, -350, 1000, 700,
			0, 0, 1000, 700,
			time_end, Color(1, 1, 1));
		break;

	default:;   // 何もしない
	}
}

void CStage::Time(){
	m_time_count--;

	if (m_time_count < 0){
		m_res.GetBGM(BGM::STAGE)->stop();
		m_info.Crear();
		m_change_scene = Type::RESULT;
		m_app_env->bgColor(Color(0, 0, 0));
	}
}

void CStage::Start(){
	if (!isStart)return;

	// タイムオーバー
	if (!m_time_count) {

		// リトライ
		if (m_app_env->isPushKey(GLFW_KEY_R)) {
			m_time_count = 30 * 60;
			isStart = false;
		}

		// タイトルに戻る
		if (m_app_env->isPushKey(GLFW_KEY_E)) {
			m_time_count = 60 * 60;
			Fade_ = 1;
			Alpha_ = 0;
			m_res.GetBGM(BGM::STAGE)->stop();
			m_change_scene = Type::TITLE;
		}

		return;
	}

	m_obj_task.Update();

	if (m_app_env->isPushKey(GLFW_KEY_L)){
		m_res.GetBGM(BGM::STAGE)->stop();
		m_info.Crear();
		m_change_scene = Type::RESULT;
		m_app_env->bgColor(Color(0, 0, 0));
	}

	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::ENMEY).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::ENMEY).End(); it++){
		if (!m_info.GetInfo(CObjectInfoManager::Type::ENMEY).GetActive(it)){
			m_app_env->bgColor(Color(0, 0, 0));
			m_change_scene = Type::RESULT;

			if (num == 3) {
				std::ofstream save("res/stage03.txt");
				if (save) {
					save << ((60 * 60) - m_time_count);
					num++;
				}
				std::ofstream ream("res/clear.txt");
				if (ream) {
					ream << 1 << std::endl;
					ream << 1 << std::endl;
					ream << 1 << std::endl;
				}
			}

			if (num == 2) {
				std::ofstream save("res/stage02.txt");
				if (save) {
					save << ((60 * 60) - m_time_count);
					num++;
				}
				std::ofstream ream("res/clear.txt");
				if (ream) {
					ream << 1 << std::endl;
					ream << 1 << std::endl;
					ream << 0 << std::endl;
				}
			}

			if (num == 1) {
				std::ofstream save("res/stage01.txt");
				if (save){
					save << ((60 * 60) - m_time_count);
					num++;
				}
				std::ofstream ream("res/clear.txt");
				if (ream){
					ream << 1 << std::endl;
					ream << 0 << std::endl;
					ream << 0 << std::endl;
				}
			}

			m_res.GetBGM(BGM::STAGE)->stop();
		}
	}
	Time();
}

void CStage::Ready(){

	// ゲームオーバーからのリトライ処理
	if (m_time_count) {
		// フェード処理を元に戻す
		if (Fade_ < 1.0f) { Fade_ += 0.02f; }
		if (Alpha_ > 0.0f) { Alpha_ -= 0.05; }
	}

	if (isStart)return;

	if (ready_count < 80)
		ready_count++;
	else if (ready_count == 80)
	{
		m_res.GetSE(SE::COUNT_SE1)->play();
		font_size += 60;
		ready_count = 0;
	}

	switch (font_size)
	{
	case 60:
		R_ = 0;
		G_ = 0;
		B_ = 1;
		break;

	case 120:
		R_ = 1;
		G_ = 1;
		B_ = 0;
		break;

	case 180:
		R_ = 1;
		G_ = 0;
		B_ = 0;

	default:
		break;
	}

	if (font_size > 60 * 3)
	{
		m_res.GetSE(SE::COUNT_SE2)->play();
		isStart = true;
		font_size = 0;
		ready_count = 0;
	}
}

void CStage::Cutin(){
	for (auto it = m_info.GetInfo(CObjectInfoManager::Type::PLAYER).Begin(); it != m_info.GetInfo(CObjectInfoManager::Type::PLAYER).End(); it++){
		if (m_info.GetInfo(CObjectInfoManager::Type::PLAYER).DynamicCast<CPlayer>(it)->GetAnime()){
			isAnime = true;
		}
	}
}