#include "ConfigManager.h"
#include "../Tools/CommonTools.h"
#include "../GameDefine/BaseType.h"
#include <string.h>
using namsepace std;
ConfigManager::loadAllFile()
{
	
}

bool ConfigManager::loadLevelFile()
{
	FILE * fp;
 	string ch;

	string path=CONFIG_ROOT_PATH;
	path.append("custom.txt");
 	if((fp=fopen(path,"r"))== NULL) )
 	{
		return false;
	}

	char buffer[BUFFLEN];
	
	 while(!feof(pf))
	 {
	 	memset(buffer,0,BUFFLEN);
		fgets(buffer,BUFFLEN,fp);
		StrContaonType conVec;
		CommonTools::split(buffer,"\t",conVec);
		if(!conVec.empty()&&conVec.size()!=3)
		{
			return false;
		}
		for(StrContaonTypeItr it=conVec.begin();it!=conVec.end();it++)
		{
			ConfigLevelData *data=new ConfigLevelData();
			data->id= std::atoi(conVec[0]);
			data->level=std::atoi(conVec[1]);
			data->exp=std::atoi(conVec[2]);
			configLevelManager[data.getIndex()]=data;
		}
	 }
	 fclose(pf);
	 return true;
}

