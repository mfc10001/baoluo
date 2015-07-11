///////////////////////////////////////////////////////////////////////////////

#ifndef _ECHO_SERVER_H_
#define _ECHO_SERVER_H_

#include "ise/main/ise.h"
#include "ise/main/ise_options.h"
#include "ise/main/ise_classes.h"
#include "ise/main/ise_sys_utils.h"
#include "ise/main/ise_socket.h"
#include "ise/main/ise_exceptions.h"
#include "ise/main/ise_server_tcp.h"
#include "ise/main/ise_application.h"
#include "ise/ext/utils/json/json.h"

#define MAX_SEND_BUFF 4086
///////////////////////////////////////////////////////////////////////////////

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


	bool msgProcess(const TcpConnectionPtr& connection,int type,Json::Value &arrayObj);

};

///////////////////////////////////////////////////////////////////////////////

#endif // _ECHO_SERVER_H_
