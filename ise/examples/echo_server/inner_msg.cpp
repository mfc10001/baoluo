#include "echo_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"
#include "game_core/ConfigManager.h"

bool AppBusiness::innerMsgProcess(const TcpConnectionPtr& connection,int type,Json::Value &arrayObj)
{

	uint32 err=1;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=PROTOCOL_INVALID;;



	switch(type)
	{
		case INNER_CREATE_ROLE:
			if(arrayObj.isMember("uid")&&arrayObj.isMember("role"))
			{
				uint32 uid = arrayObj["uid"].asUInt();
	            uint32 role = arrayObj["role"].asUInt();
				GamePlayer *player=new GamePlayer();
	            player->createChar(uid,role);
	            GamePlayerManager::instance().AddPlayer(player);
			}
			break;
		default:
			return false;
	}


	rValue["code"]=err;
	rValue["type"]=rNo;
	rValue["data"]=rData;
	string str = rValue.toStyledString();

	char buff[MAX_SEND_BUFF];
	memset(buff,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff,&len,sizeof(uint16));
	memcpy(buff+2,str.c_str(),str.length());

	connection->send(buff,len);
}


