

#ifndef _ISE_CONFIG_H_
#define _ISE_CONFIG_H_

#include "ise/main/ise.h"
#include "../bass_class/Singleton.h"
#include <map>
using namespace std;
//��ȡ�ļ���󻺳�
const uint16 BUFFLEN  = 512;

//��ȡ�����ı���Ŀ¼
const string CONFIG_ROOT_PATH ="./config/res/";


enum ConfigFile
{
	ConfigFileLevel=1,
};

struct ConfigLevelData:public BaseConfig
{
	uint32 id;
	uint32 level;
	uint32 exp;

};

class ConfigManager:public Singleton<ConfigManager>
{
	public:
		bool loadAllFile();
		bool loadLevelFile();

	private:
		typedef map<uint32,  ConfigLevelData*> configLevelType;
		configLevelType configLevelManager;



    friend class Singleton<ConfigManager>;
};

#endif

