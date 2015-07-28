#include "main_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"
#include "game_core/ConfigManager.h"
#include "game_core/StoreManager.h"


#define COMMON_METHON_GET_PLAYER  uint32 cid =connection.get()->getSocket().getHandle();\
	GamePlayer* player =ConnetManager::instance().getPlayer(cid);

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

		case PROTOCOL_EQUIP_IMPROVE_C:
			{
				COMMON_METHON_GET_PLAYER
				rNo=PROTOCOL_EQUIP_IMPROVE_S;
				uint32 thisid = arrayObj["thisid"].asUInt();
				err=player->m_improve.strengthenEquip(thisid);
			}
			break;
		case PROTOCOL_EQUIP_TREASURE_C:
			{
				COMMON_METHON_GET_PLAYER
				rNo=PROTOCOL_EQUIP_TREASURE_S;
				uint32 thisid = arrayObj["thisid"].asUInt();
				uint32 pos=arrayObj["pos"].asUInt();
				err =player->m_pack_manager.onSolt(thisid,pos);
			}
			break;
		case PROTOCOL_EQUIP_UNFIX_TREASURE_C:
			{
				COMMON_METHON_GET_PLAYER
				rNo=PROTOCOL_EQUIP_UNFIX_TREASURE_S;
				uint32 pos = arrayObj["pos"].asUInt();
				err =player->m_pack_manager.unfixSolt(pos);
			}
			break;
		case PROTOCOL_PACK_LIST_C:
			{
				COMMON_METHON_GET_PLAYER
				rNo=PROTOCOL_PACK_LIST_S;
				uint32 pos = arrayObj["pos"].asUInt();
				player->m_pack_manager.fill(rData,pos);
				rData["pack_type"]=pos;
				err=ERR_SUCCESS;
			}
			break;
        case PROTOCOL_STORE_BUY_C:
            {
                COMMON_METHON_GET_PLAYER
               // uint32 cid =connection.get()->getSocket().getHandle();
               // uint32 sizeoo=ConnetManager::instance().get
                //GamePlayer* player =ConnetManager::instance().getPlayer(cid);

                rNo=PROTOCOL_STORE_BUY_S;
                uint32 goodsId = arrayObj["id"].asUInt();
                err=StoreManager::instance().buyGoods(goodsId,player);
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
	return true;
}

