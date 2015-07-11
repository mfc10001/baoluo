///////////////////////////////////////////////////////////////////////////////

#include "echo_server.h"
#include "game_core/ConfigManager.h"
#include "ise/ext/dbi/mysql/ise_dbi_mysql.h"
#include "tools/CommonTools.h"

MySqlDatabase *m_db_conn=NULL;
IseBusiness* createIseBusinessObject()
{
    return new AppBusiness();
}

///////////////////////////////////////////////////////////////////////////////

const int RECV_TIMEOUT = 1000*5;  // ms

//-----------------------------------------------------------------------------
// ����: ��ʼ�� (ʧ�����׳��쳣)
//-----------------------------------------------------------------------------
void AppBusiness::initialize()
{
	try
	{
		bool ret=ConfigManager::instance().loadAllFile();
		if(!ret)
		{
			throw(ret);
		}

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
	catch(bool)
	{
		exit(1);
	}
    // nothing
}

//-----------------------------------------------------------------------------
// ����: ������ (���۳�ʼ���Ƿ����쳣������ʱ����ִ��)
//-----------------------------------------------------------------------------
void AppBusiness::finalize()
{
    string msg = formatString("%s stoped.", getAppExeName(false).c_str());
    std::cout << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// ����: ��ʼ���ɹ�֮��
//-----------------------------------------------------------------------------
void AppBusiness::afterInit()
{
    string msg = formatString("%s started.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// ����: ��ʼ��ʧ��
//-----------------------------------------------------------------------------
void AppBusiness::onInitFailed(Exception& e)
{
    string msg = formatString("fail to start %s.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// ����: ��ʼ��ISE������Ϣ
//-----------------------------------------------------------------------------
void AppBusiness::initIseOptions(IseOptions& options)
{
    // ���÷���������
    options.setServerType(ST_TCP);
    // ����TCP������������
    options.setTcpServerCount(1);
    // ����TCP����˿ں�
    options.setTcpServerPort(10000);
    // ����TCP�¼�ѭ���ĸ���
    options.setTcpServerEventLoopCount(1);
}

//-----------------------------------------------------------------------------
// ����: ������һ���µ�TCP����
//-----------------------------------------------------------------------------
void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    string msg = "Welcome to the simple echo server, type 'quit' to exit.\r\n";
    connection->send(msg.c_str(), msg.length());

}

//-----------------------------------------------------------------------------
// ����: �Ͽ���һ��TCP����
//-----------------------------------------------------------------------------
void AppBusiness::onTcpDisconnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpDisconnected (%s)", connection->getConnectionName().c_str());
}

//-----------------------------------------------------------------------------
// ����: TCP�����ϵ�һ���������������
//-----------------------------------------------------------------------------
void AppBusiness::onTcpRecvComplete(const TcpConnectionPtr& connection, void *packetBuffer,
    int packetSize, const Context& context)
{
    logger().writeStr("onTcpRecvComplete");

	char *dataptr=(char*)packetBuffer;

    string msg((char*)dataptr+2, packetSize-2);

	Json::Reader reader;
	Json::Value value;
	if (reader.parse(msg, value))
	{
		string str = value["type"].asString();
		int n = atoi(str.c_str());

		msgProcess(connection,n,value["data"]);

	}
/*
    msg = trimString(msg);
    if (msg == "quit")
        connection->disconnect();
    else
        connection->send((char*)packetBuffer, packetSize);
*/
    logger().writeFmt("Received message: %s", msg.c_str());
}

//-----------------------------------------------------------------------------
// ����: TCP�����ϵ�һ���������������
//-----------------------------------------------------------------------------
void AppBusiness::onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context)
{
    logger().writeStr("onTcpSendComplete");

   // connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT, RECV_TIMEOUT);
     connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}



void AppBusiness::assistorThreadExecute(AssistorThread& assistorThread, int assistorIndex)
{
	
}

