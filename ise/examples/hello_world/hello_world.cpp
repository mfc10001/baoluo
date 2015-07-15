

///////////////////////////////////////////////////////////////////////////////

#include "hello_world.h"
#include "ise/ext/dbi/mysql/ise_dbi_mysql.h"
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
    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
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
			string str = value["type"].asString();
			int n = atoi(str.c_str());

			msgProcess(connection,n,value["data"]);
		}
	}
}

