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
#define MAX_REV_BUFF 4096
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
	bool innerMsgProcess(const TcpConnectionPtr& connection,int type,uint32 cid,Json::Value &arrayObj);


	virtual void assistorThreadExecute(AssistorThread& assistorThread, int assistorIndex)

	boost::scoped_ptr<BaseTcpClient> tcpClient_;
	//IoBuffer *recvBuf_;
	boost::scoped_ptr<IoBuffer> recvBuf_;


};

///////////////////////////////////////////////////////////////////////////////


class ConnetMangaer:public Singleton<TokenManager>
{
	public:
		const TcpConnectionPtr& connection

		void add(const TcpConnectionPtr& con);
		void del(uint32 cid);
		uint32 makeCid();
		const TcpConnectionPtr* getConn(uint32 cid);
	private:
		friend class Singleton<TokenManager>;
		//�ͻ���cid
		typedef map<uint32,const TcpConnectionPtr&>  ConnetManagerMap;
		ConnetManagerMap m_con_manager;



}

#endif // _ECHO_SERVER_H_
