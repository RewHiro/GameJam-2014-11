#pragma once
#include "../Scene.h"
#include "../../resource/Resource.h"
#include "../../task/ObjectTask.h"

//========================================
//ステージクラス
//========================================
class CStage : public CScene{
public:
	CStage(std::shared_ptr<AppEnv>app_env);

	//　更新
	Type Update();

	//　描画
	void Draw();
private:
	CObjectTask m_obj_task;
	CObjectInfoManager m_info;
};

