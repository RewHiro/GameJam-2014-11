#pragma once
#include "../Object.h"
#include "../../../lib/appEnv.hpp"
#include "../item/heart/Heart.h"
#include "../item/heart/PoisonHeart.h"
#include <unordered_map>

class CItemFactory{
public:

	enum class Type{
		NORMAL,
		POISON
	};

	CItemFactory(){
		m_object_create_list.emplace(Type::NORMAL, [](Vec2f& pos){return std::make_shared<CHeart>(pos); });
		m_object_create_list.emplace(Type::POISON, [](Vec2f& pos){return std::make_shared<CPoisonHeart>(pos); });
	}

	//　オブジェクトを取得
	std::shared_ptr<Object> Getobject(const Type name, Vec2f& pos)const{
		return (m_object_create_list.find(name)->second)(pos);
	}

private:
	std::unordered_map < Type, std::function < std::shared_ptr<Object>(Vec2f& pos) >> m_object_create_list;			//　シーン生成リスト
};

