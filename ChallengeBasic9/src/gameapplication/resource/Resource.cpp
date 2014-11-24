#include "Resource.h"



CResource::CResource()
{
	RegistBG();
	RegistBGM();
}

//　背景の追加
void CResource::RegistBG(){
	m_bg.emplace(BG::TITLE, Texture("res/graph/title_graph.png"));
	m_bg.emplace(BG::STAGE, Texture("res/graph/stage_graph.png"));
}

//　BGMの追加
void CResource::RegistBGM(){
	m_bgm.emplace(BGM::TITLE, std::make_shared<Media>("res/sound/title_bg.wav"));
	m_bgm.emplace(BGM::STAGE, std::make_shared<Media>("res/sound/stage_bg.wav"));
}