#pragma once
#include "../Character.h"
#include "../../info/ObjectInfoManager.h"
#include "../../manager/ObjectManager.h"
#include  "../../../utility/CRandom.h"

class CMen : public CCharacter{
public:

	enum class Type{
		UPPERLEFT,
		UPPERRIGHT,
		LOWERRIGHT,
		LOWERLEFT
	};

	enum class Kind{
		GOOD,
		BAD
	};

	CMen(Type type);

	void Update();

	void Draw();

	bool isShot(){ return m_is_shot; }
	bool isPoisonShot(){ return m_is_poison_shot; }

private:
	Type m_type;
	CObjectInfoManager m_info;
	int m_count;
	bool m_is_shot = false;
	bool m_is_back = false;
	bool m_is_poison_shot = false;
	Kind m_kind;
	void Create();
	CRandom& m_random;
	void Reset();
	void Move();
	int reset_count = 0;
	Texture m_anime;

};

