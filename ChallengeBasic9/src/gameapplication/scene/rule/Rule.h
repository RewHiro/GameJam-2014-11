#pragma once
#include "../Scene.h"
class CRule : public CScene{
public:
	CRule(std::shared_ptr<AppEnv>app_env);
	//�@�X�V
	Type Update();

	//�@�`��
	void Draw();
	int num = 0;
};

