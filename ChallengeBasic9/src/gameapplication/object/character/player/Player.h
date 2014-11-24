#pragma once
#include "../Character.h"
#include "../../info/ObjectInfoManager.h"

class CPlayer : public CCharacter
{
public:
	CPlayer(std::shared_ptr<AppEnv>);

	//　更新
	void Update();

	//　描画
	void Draw();

private:
	std::weak_ptr<AppEnv>m_app_env;
	CObjectInfoManager m_info;
	//　移動処理
	void Move();
};

