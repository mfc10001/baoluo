///////////////////////////////////////////////////////////////////////////////

#ifndef _HELLO_WORLD_H_
#define _HELLO_WORLD_H_

#include "ise/main/ise.h"
#include "ise/ext/utils/json/json.h"
#include "game_define/Protocol.h"
///////////////////////////////////////////////////////////////////////////////

class AppBusiness : public IseBusiness
{
public:
    virtual void initIseOptions(IseOptions& options);
    virtual void onTcpConnected(const TcpConnectionPtr& connection);
    virtual void onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context);
    void initialize();


	void onTcpRecvComplete(const TcpConnectionPtr & connection,void * packetBuffer,int packetSize,const Context & context);
	bool msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj);


	void save();
};

extern MySqlDatabase *m_db_conn;
///////////////////////////////////////////////////////////////////////////////

#endif // _HELLO_WORLD_H_
