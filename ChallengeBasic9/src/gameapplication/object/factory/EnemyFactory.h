#pragma once
#include "../Object.h"
#include "../character/enemy/Slime.h"
#include "../character/enemy/Dragon.h"
#include <unordered_map>

class CEnemyFactory{
public:

	enum class Type{
		SLIME,
		DRAGON
	};

	CEnemyFactory(){
		m_object_create_list.emplace(Type::SLIME, [](float x, float y){return std::make_shared<CSlime>(x, y); });
		m_object_create_list.emplace(Type::DRAGON, [](float x, float y){return std::make_shared<CDragon>(x, y); });
	}

	//　オブジェクトを取得
	std::shared_ptr<Object> Getobject(const Type name, float x,float y)const{
		return (m_object_create_list.find(name)->second)(x,y);
	}

private:
	std::unordered_map < Type, std::function < std::shared_ptr<Object>(float,float) >> m_object_create_list;			//　シーン生成リスト

};

