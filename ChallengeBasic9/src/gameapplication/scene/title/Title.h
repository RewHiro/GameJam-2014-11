#pragma once
#include "../Scene.h"
#include "../../resource/Resource.h"
#include "../../utility/Font.h"
#include <memory>

class CSceneManager;

//========================================
//タイトルクラス
//========================================
class CTitle : public CScene{
public:
	CTitle(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();

	// 動き
	void Round_trip_y();

	float
		y_plus,
		y_;

private:
	std::unique_ptr<Font>m_font;
};

