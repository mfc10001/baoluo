///////////////////////////////////////////////////////////////////////////////

#ifndef _CHARGEN_SERVER_H_
#define _CHARGEN_SERVER_H_

#include "ise/main/ise.h"
#include "ise/ext/dbi/mysql/ise_dbi_mysql.h"
#include "ise/ext/utils/json/json.h"
#include "game_define/Protocol.h"


using namespace ise;

///////////////////////////////////////////////////////////////////////////////

extern MySqlDatabase *m_db_conn;

struct sevreinfo
{
	uint32  sid;
	string  addr;
	uint32 	port;
	string 	name;
};

class AppBusiness : public IseBusiness
{
public:
    AppBusiness() {}
    virtual ~AppBusiness() {}

    virtual void initialize();
    virtual void finalize();

    virtual void afterInit();
    virtual void onInitFailed(Exception& e);
    virtual void initIseOptions(IseOptions& options);

    virtual void onTcpConnected(const TcpConnectionPtr& connection);
    virtual void onTcpDisconnected(const TcpConnectionPtr& connection);
    virtual void onTcpRecvComplete(const TcpConnectionPtr& connection, void *packetBuffer,
        int packetSize, const Context& context);
    virtual void onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context);

	bool msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj);

private:
    void initMessage();
private:
    string message_;
    UINT64 transferredBytes_;

	map<uint32 ,sevreinfo>  server_manager_;
};

///////////////////////////////////////////////////////////////////////////////

#endif // _CHARGEN_SERVER_H_
