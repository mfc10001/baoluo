
#include "hello_world.h"
bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj)
{
	uint32 err=ERR_INNER;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=type;


	switch(type)
	{
		case PROTOCOL_CREATE_CHAR_C:
            {
			    uint32 account = arrayObj["account"].asUInt();
                uint32 role = arrayObj["role"].asUInt();
                //string cid = arrayObj["cid"].asString();
                rData["cid"]=arrayObj["cid"];
				rData["role"]=arrayObj["role"];
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

				char buff[BUFFLEN];
				memset(buff,0,BUFFLEN);
				sprintf(buff,"select count(*) as num from bl_user where account=%u",account);
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
					sprintf(buff,"insert into bl_user (account,role) values (%u,%u);  ",account,role);
					query->setSql(buff);

					try
					{
						query->execute();
						uint64 uid = query->getLastInsertId();
						rData["uid"]=(uint32)uid;
						delete res;
						res = NULL;
						err=ERR_SUCCESS;
					}
					catch(Exception)
					{
						break;
					}
				}
				else
				{
					err=ERR_EXIST_ROLE;
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

    return true;

}

