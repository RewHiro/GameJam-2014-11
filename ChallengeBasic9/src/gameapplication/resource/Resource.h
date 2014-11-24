#pragma once
#include "../Uncopyable.h"
#include "../../lib/texture.hpp"
#include "../../lib/audio.hpp"
#include <memory>
#include <unordered_map>

//========================================
//リソースクラス
//========================================

class CResource : private Uncopyable{
public:
	//　インスタンスの取得
	static CResource& GetInstance(){
		static CResource instance;
		return instance;
	}

	enum class BG{
		TITLE,
		STAGE
	};

	enum class BGM{
		TITLE,
		STAGE
	};

	enum class SE{
	};

	//　背景を取得
	Texture GetBG(const BG name)const{
		return m_bg.find(name)->second;
	}

	//　BGMを取得
	std::shared_ptr<Media> GetBGM(const BGM name)const{
		return m_bgm.find(name)->second;
	}

private:
	CResource();
	std::unordered_map<BG, Texture>m_bg;								//　背景
	std::unordered_map<BGM, std::shared_ptr<Media>>m_bgm;				//　bgm

	//　背景の追加
	void RegistBG();

	//　BGMの追加
	void RegistBGM();
};

typedef CResource::BG BG;
typedef CResource::BGM BGM;