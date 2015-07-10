#include "ConfigManager.h"
#include "../tools/CommonTools.h"
#include "../game_define/BaseType.h"
#include <string.h>

bool ConfigManager::loadAllFile()
{
	 loadLevelFile();
	 loadPLayerFile();

     return true;
}

bool ConfigManager::loadLevelFile()
{
	string path=CONFIG_ROOT_PATH;
	path.append("custom.txt");

	FILE * fp=fopen(path.c_str(),"r");
 	if(!fp)
 	{
		return false;
	}

	char buffer[BUFFLEN];

	 while(!feof(fp))
	 {
	 	memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=3)
		{
			return false;
		}
		//for(StrContaonTypeItr it=conVec.begin();it!=conVec.end();it++)
		{
			ConfigLevelData *data=new ConfigLevelData();

			data->id= atoi( conVec[0].c_str());
			data->level=atoi(conVec[1].c_str());
			data->exp=atoi(conVec[2].c_str());
			configLevelManager[data->getIndex()]=data;
		}
	 }
	 fclose(fp);
	 return true;
}



const ConfigLevelData* ConfigManager::getLevelData(uint32 id)
{
	
}
const ConfigPlayerData* ConfigManager::getPlayerData(uint32 id)
{
	
}

