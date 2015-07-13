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
                string account = arrayObj["account"].asString();
                string role = arrayObj["role"].asString();
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

				char buff[BUFFLEN];
				memset(buff,0,BUFFLEN);
				sprintf(buff,"select count(*) as num from bl_user where account=%s",account.c_str());
                query->setSql(buff);
                MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
                if(!res->isEmpty() && res->next())
                {
					MySqlField* num = static_cast<MySqlField *> (res->getFields("num"));
					if(num->asInteger()>0)
					{
                        break;
					}
                    delete res;
                    res = NULL;

					memset(buff,0,BUFFLEN);
                    sprintf(buff,"insert into bl_user (account,role) values (%s,%s);  ",account.c_str(),role.c_str());
                    query->setSql(buff);

                    try
                    {
                        query->execute();
                        uint64 charid = query->getLastInsertId();
                        GamePlayer *player=new GamePlayer();
						int n = atoi(str.c_str());
						
						
                        player->createChar(charid,n);
                        GamePlayerManager::instance().AddPlayer(player);
						
						
                        delete res;
                        res = NULL;
                    }
                    catch(Exception)
                    {
                        break;
                    }
                }
                */
			}
			break;
		case PROTOCOL_ENTER_CS:
			{
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

