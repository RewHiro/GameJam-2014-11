#pragma once
#include "../Scene.h"
#include "../../resource/Resource.h"
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

private:
	
};

