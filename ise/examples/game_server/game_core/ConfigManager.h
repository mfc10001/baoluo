

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

struct ConfigLevelData:public BaseConfig
{
	uint32 id;
	uint32 level;
	uint32 exp;
    uint32 getIndex(){return id;};
};



struct ConfigPlayerData:public BaseConfig
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

class ConfigManager:public Singleton<ConfigManager>
{
	public:
		bool loadAllFile();
		bool loadLevelFile();
		bool loadPLayerFile();

		const ConfigLevelData* getLevelData(uint32 id);
		const ConfigPlayerData* getPlayerData(uint32 id);


	private:
		typedef map<uint32,  ConfigLevelData*> configLevelType;
		configLevelType configLevelManager;

		typedef map<uint32,  ConfigPlayerData*> configPlayerType;
		configPlayerType configPlayerManager;

    friend class Singleton<ConfigManager>;
};

#endif

