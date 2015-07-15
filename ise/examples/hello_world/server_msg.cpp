
#include "hello_world.h"
bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,int type,Json::Value &arrayObj)
{
	uint32 err=ERR_INNER;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=type;


	switch(type)
	{
		case PROTOCOL_CREATE_CHAR_C:
            {
			    string account = arrayObj["account"].asString();
                string role = arrayObj["role"].asString();
                //string cid = arrayObj["cid"].asString();
                rData["cid"]=arrayObj["cid"];
				rData["role"]=arrayObj["role"];
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
						uint64 uid = query->getLastInsertId();
						memset(buff,0,BUFFLEN);
						sprintf(buff,"%llu",uid);
						rData["uid"]=buff;
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
					err=ERR_EXIST_ROLE
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

