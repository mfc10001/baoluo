

#ifndef _ISE_CONFIG_H_
#define _ISE_CONFIG_H_

#include "ise/main/ise.h"
#include "../base_class/Singleton.h"


//读取文件最大缓冲
const uint16 BUFFLEN  = 512

//读取配置文本跟目录
const string CONFIG_ROOT_PATH ="./config/res/"


enum ConfigFile
{
	ConfigFileLevel=1;
}

class ConfigLevelData:public BaseConfig
{
	uint32 id;
	uint32 level;
	uint32 exp;
	
}

class ConfigManager:public Singleton
{
	public:
		bool loadAllFile();
		bool loadLevelFile();
		
	private:
		typedef map<uint32,  ConfigLevelData> configLevelType;
		configLevelType configLevelManager;
}

#endif

