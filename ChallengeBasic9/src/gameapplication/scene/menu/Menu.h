#pragma once
#include "../Scene.h"
#include "../../utility/Font.h"

enum point_u
{
	start,
	lanking,
	explain
};

class Menu : public CScene{
public:
	Menu(std::shared_ptr<AppEnv>app_env);

	//�@�X�V
	Type Update();

	//�@�`��
	void Draw();

	//�@�L�[����
	void Key_control_u();

	// ������
	void flush_initialize();

	//�@���݂̃J�[�\���ʒu
	int cursor_point;

	//�@�_��
	float
		flush_start,
		flush_lanking,
		flush_explain,

		flush_,
		flush_plus;

private:
	std::unique_ptr<Font>m_font;
};



