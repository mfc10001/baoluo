

///////////////////////////////////////////////////////////////////////////////

#include "db_server.h"
#include "ise/ext/dbi/mysql/ise_dbi_mysql.h"
#include "game_define/BaseType.h"
//-----------------------------------------------------------------------------
MySqlDatabase *m_db_conn=NULL;

IseBusiness* createIseBusinessObject()
{
    return new AppBusiness();
}
void AppBusiness::initialize()
{
	try
	{
        m_db_conn=new MySqlDatabase();
        DbConnParams *param=m_db_conn->getDbConnParams();
        param->setHostName("192.168.18.147");
        param->setUserName("root");
        param->setPassword("123456");
        param->setDbName("baoluo_zs");
        param->setPort(3306);
        DbOptions *op = m_db_conn ->getDbOptions();
        op->setInitialCharSet("utf-8");
        MySqlConnection *dbconn = static_cast<MySqlConnection *> (m_db_conn->createDbConnection());
        dbconn->doConnect();
	}
    catch(exception)
    {
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////////

void AppBusiness::initIseOptions(IseOptions& options)
{
    options.setServerType(ST_TCP);
    options.setTcpServerPort(22306);
}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);

}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context)
{
    //connection->disconnect();
   // connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}

void AppBusiness::onTcpRecvComplete(const TcpConnectionPtr & connection,void * packetBuffer,int packetSize,const Context & context)
{

	char *dataptr=(char*)packetBuffer;

    string msg((char*)dataptr+2, packetSize-2);

	Json::Reader reader;
	Json::Value value;
	if (reader.parse(msg, value))
	{
		if(value.isMember("type"))
		{
			uint32 n = value["type"].asUInt();
			msgProcess(connection,n,value["data"]);
		}
	}
    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}
void AppBusiness::savePlayer(Json::Value &arrayObj)
{
	uint32 uid=arrayObj["base"]["uid"].asUInt();
    char buff[SQL_BUFFLEN]={0};
	MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

	sprintf(buff,"update bl_user set level = %u,exp = %u,physicsAttack = %u,magicAttack = %u,barmor=%u,bresistance=%u,hp=%u,hit=%u,dodge=%u,crit=%u.money=%u,diamond=%u where uid=%u",
		arrayObj["base"]["level"].asUInt(),arrayObj["base"]["exp"].asUInt(),arrayObj["base"]["physicsAttack"].asUInt(),
		arrayObj["base"]["magicAttack"].asUInt(),arrayObj["base"]["barmor"].asUInt(),arrayObj["base"]["bresistance"].asUInt(),
		arrayObj["base"]["hp"].asUInt(),arrayObj["base"]["hit"].asUInt(),arrayObj["base"]["dodge"].asUInt(),
		arrayObj["base"]["crit"].asUInt(),arrayObj["base"]["money"].asUInt(),arrayObj["base"]["diamond"].asUInt(),uid);

	query->setSql(buff);

	try
	{
		query->execute();

	}
	catch(Exception)
	{


	}

	bzero(buff,SQL_BUFFLEN);
	//if(arrayObj["package"]["base_type"] == ItemType_Equip)
	/*{
		sprintf(buff,"replace into  bl_item (itemid,uid,thisid,baseid,num,base_type,Strengthen,Hole1,Hole2,Hole3,Hole4) values (%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u)",
			arrayObj["package"]["baseid"].asUInt(),uid,arrayObj["package"]["thisid"].asUInt(),
			arrayObj["package"]["num"].asUInt(),arrayObj["package"]["base_type"].asUInt(),
			arrayObj["package"]["Strengthen"].asUInt(),arrayObj["package"]["Hole1"].asUInt(),
			arrayObj["package"]["Hole2"].asUInt(),arrayObj["package"]["Hole3"].asUInt(),
			arrayObj["package"]["Hole4"].asUInt());
	}*/

	{
		
		sprintf(buff,"replace into  bl_item (uid,item_bin) values (%u,%s)",uid,arrayObj["package"]["uin"].asString().c_str());

		/*
		sprintf(buff,"replace into  bl_item (itemid,uid,thisid,baseid,num,base_type) values (%u,%u,%u,%u,%u,%u)",
			arrayObj["package"]["baseid"].asUInt(),uid,arrayObj["package"]["thisid"].asUInt(),
			arrayObj["package"]["num"].asUInt(),arrayObj["package"]["base_type"].asUInt());
		*/
	}

	query->setSql(buff);

	try
	{
		query->execute();

	}
	catch(Exception)
	{


	}


}


