#include "Slime.h"


CSlime::CSlime(float x,float y)
{
	m_model.Position(x, y);
	m_hit_model.Position(Vec2f(x, y));
	m_color = Color(0, 0, 1);
}