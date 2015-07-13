

///////////////////////////////////////////////////////////////////////////////

#include "hello_world.h"

//-----------------------------------------------------------------------------

IseBusiness* createIseBusinessObject()
{
    return new AppBusiness();
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

    string msg = "Hello World!\r\n";


    connection->send(msg.c_str(), msg.length());
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
		string str = value["type"].asString();
		int n = atoi(str.c_str());

		msgProcess(connection,n,value["data"]);
	}
}

