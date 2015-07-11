#include "echo_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"


bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,int type,Json::Value &arrayObj)
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
		case PROTOCOL_AUTH_CS:
            {
                string account = arrayObj["account"].asString();
                int n = atoi(account.c_str());

                string token=arrayObj["token"].asString();
                //err= TokenManager::instance().Authentication(arrayObj["uid"],arrayObj["token"]);
                rNo=PROTOCOL_AUTH_CS;
                break;
            }
		case PROTOCOL_LOGIN_CS:

			break;
		case PROTOCOL_CHAR_LIST_CS:


			break;

		case PROTOCOL_CREATE_CHAR_CS:
            {
                string account = arrayObj["account"].asString();
                string role = arrayObj["role"].asString();
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

				char buff[BUFFLEN];
				memsetbuff,0,BUFFLEN);
				sprintf(buff,"insert into bl_user (account,role) values (%s,%s) SELECT @@IDENTITY AS uid ",account.c_str(),role.c_str())
				query->setSql(sql);

				MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
				while(!res->isEmpty() && res->next())
				{
					MySqlField* charid = static_cast<MySqlField *> (res->getFields("uid"));
					GamePlayer *player=new GamePlayer();

	                //player->createChar(arrayObj["chartype"])

	                GamePlayerManager::instance().AddPlayer(player);
				}


			}
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

	char buff[MAX_SEND_BUFF];
	memset(buff,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff,&len,sizeof(uint16));
	memcpy(buff+2,str.c_str(),str.length());

	connection->send(buff,len);
}

