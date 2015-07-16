#include "main_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"
#include "game_core/ConfigManager.h"

bool AppBusiness::innerMsgProcess(TcpConnection& connection,uint32 type,Json::Value &arrayObj,uint32 code) const
{

	uint32 err=1;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=PROTOCOL_INVALID;;



	switch(type)
	{
		case PROTOCOL_CREATE_CHAR_C:
			{
	            rNo=PROTOCOL_CREATE_CHAR_S;
				if(code!=ERR_SUCCESS)
				{
					break;
				}
/*
				uint32 uid = arrayObj["uid"].asUInt();
	            uint32 role = arrayObj["role"].asUInt();
				GamePlayer *player=new GamePlayer();
	            player->createChar(uid,role);
	            GamePlayerManager::instance().AddPlayer(player);
 */
				err=ERR_SUCCESS;

			}
			break;
		case PROTOCOL_ENTER_C:
			{
				uint32 uid = arrayObj["uid"].asUInt();
				rNo=PROTOCOL_ENTER_S;
				if(code!=ERR_SUCCESS)
				{
					break;
				}

				GamePlayer *player = GamePlayerManager::instance().getPlayer(uid);
				if(player)
				{
					err=ERR_EXIST_AL_LOGIN;
					break;
				}
				player=new GamePlayer();
				player->init(arrayObj);
				GamePlayerManager::instance().AddPlayer(player);
				player->fillClientData(rData);
				err=ERR_SUCCESS;
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
	LinuxTcpConnection*  pp =  static_cast<LinuxTcpConnection*> (&connection);
	pp->send(buff,len);

//	connection.sendBaseBuff(buff,len);
	//connection.sendBaseBuff(buff,len);
	return true;
}


