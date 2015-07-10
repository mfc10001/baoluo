#include "echo_sevre.h"
#include "GameCore/GamePlayer.h"
#include "GameCore/GamePlayerManager.h"


bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,uint32 &type,Json::Value &arrayObj)
{
	uint32 err=1;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo;
	Protocol =PROTOCOL_INVALID;
	switch(type)
	{
		case PROTOCOL_TOKEN_C:
			TokenManager::instance().AddToken(arrayObj["uid"],arrayObj["token"]);
			
			return true;
		case PROTOCOL_AUTH_CS:
			
			err= TokenManager::instance().Authentication(arrayObj["uid"],arrayObj["token"]);
			rNo=PROTOCOL_AUTH_CS;
			break;

		case PROTOCOL_LOGIN_CS:
			
			break;
		case PROTOCOL_CHAR_LIST_CS:
			
			
			break;

		case PROTOCOL_CREATE_CHAR_CS:
			GamePlayer *player=new GamePlayer();
			
			player->createChar(arrayObj["chartype"])

			GamePlayerManager::instance().AddPlayer(player);
			break;
		case PROTOCOL_CHAR_CHOSE_CS:
			
			break;
		default:
			return false;
	}


	rValue["code"]=err;
	rValue["type"]=rNo;
	rValue["data"]=rData;
	string str = rValue.toStyledString();

	char buff[MAX_SEND_BUFF]=0
	memset(buff,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff,&len,sizeof(uint16));
	memcpy(buff+2,str,str.length())
	
	connection->send(buff,len);
}

