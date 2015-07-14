#include "echo_server.h"
#include "game_core/GamePlayer.h"
#include "game_core/GamePlayerManager.h"
#include "game_define/Protocol.h"
#include "tools/CommonTools.h"
#include "game_core/ConfigManager.h"

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
				/*
                rData["account"]=arrayObj["account"];
                rData["role"]=arrayObj["role"];
            	rValue["type"]=INNER_CREATE_ROLE;
                rValue["data"]=rData;
                string str = rValue.toStyledString();
                char buff[MAX_SEND_BUFF];
                memset(buff,0,MAX_SEND_BUFF);
                uint16 len=str.length()+2;
                memcpy(buff,&len,sizeof(uint16));
                memcpy(buff+2,str.c_str(),str.length());
                if(tcpClient_->getConnection().sendBaseBuff(buff,len)>0)
                {
					return true;
				}
				return false;
				*/
			}
			break;
		case PROTOCOL_ENTER_CS:
			{
                /*
                string account = arrayObj["account"].asString();

				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());
				char buff[BUFFLEN];
				memset(buff,0,BUFFLEN);
				sprintf(buff,"select count(*) as num from bl_user where account=%s",account.c_str());
                query->setSql(buff);
                MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
                while(!res->isEmpty() && res->next())
                {

				}
				*/
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

