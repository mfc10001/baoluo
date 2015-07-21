

#ifndef _ISE_CONFIG_H_
#define _ISE_CONFIG_H_

#include "ise/main/ise.h"
#include "../bass_class/Singleton.h"

//读取文件最大缓冲


//读取配置文本跟目录
const string CONFIG_ROOT_PATH ="./res/";


enum ConfigFile
{
	ConfigFileLevel=1,
};

struct LevelDataEntry:public Entry
{
	uint32 id;
	uint32 level;
	uint32 exp;
    uint32 getIndex(){return id;};
};



struct PlayerDataEntry:public Entry
{
	uint32 id;
	uint16 physicsAttack;
	uint16 magicAttack;
	uint16 barmor;
	uint16 bresistance;
	uint16 hp;
	uint16 hit;
	uint16 dodge;
	uint16 crit;
	uint16 opposeCrit;
	uint16 physicsAttackz;
	uint16 magicAttackz;
	uint16 barmorz;
	uint16 bresistancez;
	uint16 hpz;
	uint16 hitz;
	uint16 dodgez;
	uint16 critz;
	uint16 opposeCritz;
    uint32 getIndex(){return id;};
};

struct ItemDataEntry:public Entry
{
	uint32 itemid;
	char   name[MAX_NAMESIZE];
	uint8 quality;
	uint8 type;
	uint16 level;
	uint8 use_type;
	uint16 effect;
	uint32 cd;
	uint32 add_max;
};

struct EquipDataEntry:public Entry
{
	uint32 itemid;
	char   name[MAX_NAMESIZE];	
	uint8 profession;
	uint8 part;	
	uint16 grade;
	uint8 quality;
	uint32 icon;
	uint16 physicsAttack;
	uint16 magicAttack;
	uint16 n_barmor;
	uint16 bresistance;
	uint32 hp;
	uint32 hit;
	uint16 dodge;
	uint16 n_crit;
	uint16 n_opposeCrit;
	
};


class ConfigManager:public Singleton<ConfigManager>
{
	public:
		bool loadAllFile();
		bool loadLevelFile();
		bool loadPLayerFile();

		const ConfigLevelData* getLevelData(uint32 id);
		const ConfigPlayerData* getPlayerData(uint32 id);


	private:
		typedef map<uint32,  LevelDataEntry*> configLevelType;
		configLevelType configLevelManager;

		typedef map<uint32,  PlayerDataEntry*> configPlayerType;
		configPlayerType configPlayerManager;

	


    friend class Singleton<ConfigManager>;
};

#endif

