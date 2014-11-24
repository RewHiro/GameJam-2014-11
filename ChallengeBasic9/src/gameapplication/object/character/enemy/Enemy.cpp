#include "Enemy.h"
#include "../player/Player.h"

CEnemy::CEnemy():
m_count(0)
{
}

//　更新
void CEnemy::Update(){
	if (!m_is_active)return;
	//m_count++;
	if (m_count == 180){
		m_is_delete = true;
	}

}

//　描画
void CEnemy::Draw(){
	if (!m_is_active)return;
	drawCircle(m_model.GetPosX(), m_model.GetPosY(), 60, 60, 20, 5, m_color);
}