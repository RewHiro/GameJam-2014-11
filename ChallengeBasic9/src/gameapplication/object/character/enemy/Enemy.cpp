#include "Enemy.h"
#include "../player/Player.h"

CEnemy::CEnemy():
m_count(0)
{
}

//�@�X�V
void CEnemy::Update(){
	if (!m_is_active)return;
	//m_count++;
	if (m_count == 180){
		m_is_delete = true;
	}
}

//�@�`��
void CEnemy::Draw(){
	if (!m_is_active)return;
}