///////////////////////////////////////////////////////////////////////////////

#ifndef _HELLO_WORLD_H_
#define _HELLO_WORLD_H_

#include "ise/main/ise.h"

using namespace ise;

///////////////////////////////////////////////////////////////////////////////

class AppBusiness : public IseBusiness
{
public:
    virtual void initIseOptions(IseOptions& options);
    virtual void onTcpConnected(const TcpConnectionPtr& connection);
    virtual void onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context);
	


	void onTcpRecvComplete(const TcpConnectionPtr & connection,void * packetBuffer,int packetSize,const Context & context);
	bool msgProcess(const TcpConnectionPtr& connection,int type,Json::Value &arrayObj);
};


///////////////////////////////////////////////////////////////////////////////

#endif // _HELLO_WORLD_H_
