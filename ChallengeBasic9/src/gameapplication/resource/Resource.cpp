#include "Resource.h"



CResource::CResource()
{
	RegistBG();
	RegistBGM();
	m_item.emplace(Item::NORMAL, Texture("res/graph/UI GAMEjam.png"));

	m_player.emplace_back(Texture("res/graph/player_left.png"));
	m_player.emplace_back(Texture("res/graph/player_right.png"));

	m_se.emplace(SE::HEART_HIT, std::make_shared<Media>("res/sound/heart_hit.wav"));
	m_se.emplace(SE::POISON_HEART_HIT, std::make_shared<Media>("res/sound/poison_hit.wav"));
	m_se.emplace(SE::BOS_HIT, std::make_shared<Media>("res/sound/boss_hit.wav"));
	m_se.emplace(SE::MENU_SE, std::make_shared<Media>("res/sound/menu_se.wav"));
	m_se.emplace(SE::COUNT_SE1, std::make_shared<Media>("res/sound/count_1.wav"));
	m_se.emplace(SE::COUNT_SE2, std::make_shared<Media>("res/sound/count_2.wav"));
	m_se.emplace(SE::YA, std::make_shared<Media>("res/sound/ya.wav"));
	m_se.emplace(SE::NORMAL_ATTACK, std::make_shared<Media>("res/sound/nomarl_atttack.wav"));
	m_se.emplace(SE::SPECIAL, std::make_shared<Media>("res/sound/special_attack.wav"));

	m_player_ui.emplace_back(Texture("res/graph/player_ui01.png"));
	m_player_ui.emplace_back(Texture("res/graph/player_ui02.png"));
	m_player_ui.emplace_back(Texture("res/graph/player_ui03.png"));

	m_player_damage.emplace_back(Texture("res/graph/player_damage_left.png"));
	m_player_damage.emplace_back(Texture("res/graph/player_damage_right.png"));
	
	m_boss.emplace_back(Texture("res/graph/boss_1_128.png"));
	m_boss.emplace_back(Texture("res/graph/boss_01_damage.png"));
	m_boss.emplace_back(Texture("res/graph/boss_01_naki.png"));
	
	m_men.emplace(Men::LOWER_RIGHT, Texture("res/graph/boy_rd.png"));
	m_men.emplace(Men::UPPER_RIGHT, Texture("res/graph/boy_ru.png"));
	m_men.emplace(Men::LOWER_LEFT, Texture("res/graph/boy_ld.png"));
	m_men.emplace(Men::UPPER_LEFT, Texture("res/graph/bay_lu.png"));

	m_shot.emplace(Shot::NORMAL, Texture("res/graph/normal_shot.png"));
	m_shot.emplace(Shot::SPECIAL, Texture("res/graph/special_shot.png"));
	m_shot.emplace(Shot::STRING, Texture("res/graph/shot_string.png"));

	m_anime_cut.emplace(Anime::CHAR, Texture("res/graph/cutin_0.png"));
	m_anime_cut.emplace(Anime::BG, Texture("res/graph/cutin2.png"));
}

//Å@îwåiÇÃí«â¡
void CResource::RegistBG(){
	m_bg.emplace(BG::TITLE, Texture("res/graph/haikei.png"));
	m_bg.emplace(BG::STAGE, Texture("res/graph/gamepack.png"));
	m_bg.emplace(BG::STAGE_PLAY, Texture("res/graph/room.png"));
	m_bg.emplace(BG::UI, Texture("res/graph/UI.png"));
	m_bg.emplace(BG::TITLE_STRING, Texture("res/graph/EnterStart.png"));
	m_bg.emplace(BG::TITLE_2, Texture("res/graph/haikei2.png"));
	m_bg.emplace(BG::RULE1, Texture("res/graph/rule1.png"));
	m_bg.emplace(BG::RULE2, Texture("res/graph/rule2.png"));
	m_bg.emplace(BG::RULE3, Texture("res/graph/rule3.png"));
}

//Å@BGMÇÃí«â¡
void CResource::RegistBGM(){
	m_bgm.emplace(BGM::TITLE, std::make_shared<Media>("res/sound/title.wav"));
	m_bgm.emplace(BGM::STAGE, std::make_shared<Media>("res/sound/stage.wav"));
	m_bgm.emplace(BGM::MENU, std::make_shared<Media>("res/sound/menu.wav"));
	m_bgm.emplace(BGM::CLEAR, std::make_shared<Media>("res/sound/clear.wav"));
	m_bgm.emplace(BGM::GAMEOVER, std::make_shared<Media>("res/sound/gameover.wav"));
}