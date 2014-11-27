#pragma once
#include "../Scene.h"
#include "../../resource/Resource.h"
#include "../../utility/Font.h"
#include <memory>

class CSceneManager;

//========================================
//�^�C�g���N���X
//========================================
class CTitle : public CScene{
public:
	CTitle(std::shared_ptr<AppEnv>app_env);

	//�@�X�V
	Type Update();

	//�@�`��
	void Draw();

	// ����
	void Round_trip_y();

	float
		y_plus,
		y_;

private:
	std::unique_ptr<Font>m_font;
};

