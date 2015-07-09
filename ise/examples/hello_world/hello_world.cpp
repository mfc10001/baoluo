

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
    options.setTcpServerPort(7272);
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
    connection->disconnect();
}

void AppBusiness::onTcpRecvComplete(const TcpConnectionPtr & connection,void * packetBuffer,int packetSize,const Context & context)
{
	string msg = "Hello World!\r\n";
	
	connection->recv(SELFT_PACKET_SPLITTER);
}

