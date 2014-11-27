#pragma once
#include "../Object.h"
#include "../character/men/Men.h"
#include <unordered_map>

class CMenFactory{
public:

	enum class Type{
		UPPERLEFT,
		UPPERRIGHT,
		LOWERRIGHT,
		LOWERLEFT
	};

	CMenFactory(){
		m_object_create_list.emplace(Type::UPPERLEFT, [](){return std::make_shared<CMen>(CMen::Type::UPPERLEFT); });
		m_object_create_list.emplace(Type::UPPERRIGHT, [](){return std::make_shared<CMen>(CMen::Type::UPPERRIGHT); });
		m_object_create_list.emplace(Type::LOWERRIGHT, [](){return std::make_shared<CMen>(CMen::Type::LOWERRIGHT); });
		m_object_create_list.emplace(Type::LOWERLEFT, [](){return std::make_shared<CMen>(CMen::Type::LOWERLEFT); });
	}

	//　オブジェクトを取得
	std::shared_ptr<Object> Getobject(const Type name)const{
		return (m_object_create_list.find(name)->second)();
	}

private:
	std::unordered_map < Type, std::function < std::shared_ptr<Object>() >> m_object_create_list;			//　シーン生成リスト

};