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
                uint32 aid = arrayObj["AID"].asUInt();

                string token=arrayObj["token"].asString();
                TokenManager::instance().AddToken(aid,token);
				return true;
            }
			return true;
		case PROTOCOL_AUTH_C:
            {
                uint32 aid = arrayObj["AID"].asUInt();
                string token=arrayObj["token"].asString();
                //uint32 uid=arrayObj["uid"].asUInt();
                err= TokenManager::instance().Authentication(aid,token);
                if(err==ERR_SUCCESS)
                {
                    ConnetManager::instance().add(connection);
                }
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
	return true;
}

