
#include "db_server.h"
bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj)
{
	uint32 err=ERR_INNER;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=type;

	char buff[BUFFLEN];
	memset(buff,0,BUFFLEN);

	switch(type)
	{
		case PROTOCOL_CREATE_CHAR_C:
            {
				rNo=PROTOCOL_CREATE_CHAR_C;
			    uint32 aid = arrayObj["AID"].asUInt();
                uint32 role = arrayObj["role"].asUInt();
                rData["cid"]=arrayObj["cid"];
				rData["role"]=arrayObj["role"];
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

				sprintf(buff,"select count(*) as num from bl_user where AID=%u",aid);
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
					sprintf(buff,"insert into bl_user (AID,role) values (%u,%u);  ",aid,role);
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

		case PROTOCOL_ENTER_C:
			{
				rNo=PROTOCOL_ENTER_C;
				rData["cid"]=arrayObj["cid"];
				uint32 aid = arrayObj["AID"].asUInt();
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());
				sprintf(buff,"select *  from bl_user where AID=%u",aid);
                query->setSql(buff);
                MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
				if(!res->isEmpty() && res->next())
				{
					err=ERR_SUCCESS;
					MySqlField* uid = static_cast<MySqlField *> (res->getFields("uid"));
					MySqlField* name = static_cast<MySqlField *> (res->getFields("name"));
					MySqlField* role = static_cast<MySqlField *> (res->getFields("role"));
					MySqlField* level = static_cast<MySqlField *> (res->getFields("level"));
					MySqlField* exp = static_cast<MySqlField *> (res->getFields("exp"));
					MySqlField* physicsAttack = static_cast<MySqlField *> (res->getFields("physicsAttack"));
					MySqlField* magicAttack = static_cast<MySqlField *> (res->getFields("magicAttack"));
					MySqlField* barmor = static_cast<MySqlField *> (res->getFields("barmor"));
					MySqlField* bresistance = static_cast<MySqlField *> (res->getFields("bresistance"));
					MySqlField* hp = static_cast<MySqlField *> (res->getFields("hp"));
					MySqlField* hit = static_cast<MySqlField *> (res->getFields("hit"));
					MySqlField* dodge = static_cast<MySqlField *> (res->getFields("dodge"));
					MySqlField* crit = static_cast<MySqlField *> (res->getFields("crit"));


					MySqlField* initflag = static_cast<MySqlField *> (res->getFields("initFlag"));
					if(initflag->asInteger()==1)
                    {
                        rData["level"]=level->asInteger();
                        rData["exp"]=exp->asInteger();
                        rData["physicsAttack"]=physicsAttack->asInteger();
                        rData["magicAttack"]=magicAttack->asInteger();
                        rData["barmor"]=barmor->asInteger();
                        rData["bresistance"]=bresistance->asInteger();
                        rData["hp"]=hp->asInteger();
                        rData["hit"]=hit->asInteger();
                        rData["dodge"]=dodge->asInteger();
                        rData["crit"]=crit->asInteger();
                    }
					rData["uid"]=uid->asInteger();
					rData["name"]=name->asString();
					rData["role"]=uid->asInteger();
                    rData["initFlag"]=initflag->asInteger();

				}

			}
		case INNER_SAVE_DATA:
			{
				save(arrayObj);
				return true;
			}
        default:
                return false;

	}

	rValue["code"]=err;
	rValue["type"]=rNo;
	rValue["data"]=rData;
	string str = rValue.toStyledString();

	char buff_send[MAX_SEND_BUFF];
	memset(buff_send,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff_send,&len,sizeof(uint16));
	memcpy(buff_send+2,str.c_str(),str.length());

	connection->send(buff_send,len);

    return true;

}

