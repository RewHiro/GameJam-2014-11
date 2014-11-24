#include "Dragon.h"


CDragon::CDragon(float x, float y)
{
	m_model.Position(x, y);
	m_hit_model.Position(x, y);
	m_color = Color(1, 1, 0);
}