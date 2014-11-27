#pragma once
#include "../Uncopyable.h"
#include "../../lib/texture.hpp"
#include "../../lib/audio.hpp"
#include <memory>
#include <unordered_map>

//========================================
//���\�[�X�N���X
//========================================

class CResource : private Uncopyable{
public:
	//�@�C���X�^���X�̎擾
	static CResource& GetInstance(){
		static CResource instance;
		return instance;
	}

	enum class BG{
		TITLE,
		STAGE,
		STAGE_PLAY,
		UI,
		TITLE_STRING,
		TITLE_2,
		RULE1,
		RULE2,
		RULE3
	};

	enum class Men{
		LOWER_RIGHT,
		UPPER_RIGHT,
		LOWER_LEFT,
		UPPER_LEFT,
	};

	enum class Shot{
		NORMAL,
		SPECIAL,
		STRING
	};

	enum class BGM{
		TITLE,
		STAGE,
		MENU,
		CLEAR,
		GAMEOVER
	};

	enum class SE{
		HEART_HIT,
		POISON_HEART_HIT,
		BOS_HIT,
		MENU_SE,
		COUNT_SE1,
		COUNT_SE2,
		YA,
		NORMAL_ATTACK,
		SPECIAL
	};

	enum class Item{
		NORMAL,
		POISON
	};

	enum class Anime{
		CHAR,
		BG
	};

	//�@�w�i���擾
	Texture GetBG(const BG name)const{
		return m_bg.find(name)->second;
	}

	//�@�w�i���擾
	Texture GetItem(const Item name)const{
		return m_item.find(name)->second;
	}

	//�@BGM���擾
	std::shared_ptr<Media> GetBGM(const BGM name)const{
		return m_bgm.find(name)->second;
	}

	//�@BGM���擾
	std::shared_ptr<Media> GetSE(const SE name)const{
		return m_se.find(name)->second;
	}

	Texture GetPlayer(int i){
		return m_player[i];
	}

	Texture GetPlayerUI(int i){
		return m_player_ui[i];
	}

	Texture GetPlayerDamage(int i){
		return m_player_damage[i];
	}

	Texture GetBoss(int i){
		return m_boss[i];
	}

	Texture GetMen(const Men name)const{
		return m_men.find(name)->second;
	}

	Texture GetShot(const Shot name)const{
		return m_shot.find(name)->second;
	}

	Texture GetAnimeCut(const Anime name)const{
		return m_anime_cut.find(name)->second;
	}




private:
	CResource();
	std::unordered_map<BG, Texture>m_bg;								//�@�w�i
	std::unordered_map<BGM, std::shared_ptr<Media>>m_bgm;				//�@bgm
	std::unordered_map<SE, std::shared_ptr<Media>>m_se;				//�@bgm


	std::unordered_map<Item, Texture>m_item;								//�@�A�C�e��
	std::unordered_map<Men, Texture>m_men;								//�@�A�C�e��
	std::vector<Texture>m_player;								//�@�A�C�e��
	std::vector<Texture>m_player_damage;								//�@�A�C�e��
	std::vector<Texture>m_player_ui;								//�@�A�C�e��
	std::vector<Texture>m_boss;								//�@�A�C�e��
	std::unordered_map<Shot, Texture>m_shot;								//�@�A�C�e��

	std::unordered_map<Anime, Texture>m_anime_cut;								//�@�A�C�e��

	//�@�w�i�̒ǉ�
	void RegistBG();

	//�@BGM�̒ǉ�
	void RegistBGM();
};

typedef CResource::BG BG;
typedef CResource::Item Item;
typedef CResource::BGM BGM;
typedef CResource::SE SE;