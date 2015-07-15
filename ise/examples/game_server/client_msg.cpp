#include "main_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"
#include "game_core/ConfigManager.h"

bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj)
{
	uint32 err=1;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=PROTOCOL_INVALID;;

	switch(type)
	{
		case PROTOCOL_TOKEN_C:
            {
                string account = arrayObj["account"].asString();
                int n = atoi(account.c_str());
                uint32 m=uint32(n);
                string token=arrayObj["token"].asString();
                TokenManager::instance().AddToken(m,token);
            }
			return true;
		case PROTOCOL_AUTH_C:
            {
                string account = arrayObj["account"].asString();
                int n = atoi(account.c_str());

                string token=arrayObj["token"].asString();
                uint32 uid=arrayObj["uid"].asUInt();

                err= TokenManager::instance().Authentication( uid,token);
                rNo=PROTOCOL_AUTH_S;
                break;
            }


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

