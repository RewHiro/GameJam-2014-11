#pragma once
#include "../Object.h"
#include "../../resource/Resource.h"

class CItem : public Object{
public:
	CItem() :
		m_res(CResource::GetInstance()){}
protected:
	CResource& m_res;
};
