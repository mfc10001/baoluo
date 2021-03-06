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
#include "game_define/Protocol.h"

///////////////////////////////////////////////////////////////////////////////
extern   TcpClient* tcpClient_;
//boost::scoped_ptr<TcpClient> tcpClient_;
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
	bool innerMsgProcess(TcpConnection& connection,uint32 type,Json::Value &arrayObj,uint32 code) const;


	virtual void assistorThreadExecute(AssistorThread& assistorThread, int assistorIndex);

	static uint32 sendToDb(Json::Value &arrayObj);

	TimerId addTimer(Timestamp expiration, INT64 interval, const TimerCallback& callback);


	void loop();

	bool isExist(uint32 pro);
	void addForwardPro(uint32 pro);

	//IoBuffer *recvBuf_;


	boost::scoped_ptr<IoBuffer> recvBuf_;

	BaseSet  forward_;


};

///////////////////////////////////////////////////////////////////////////////

class GamePlayer;
class ConnetManager:public Singleton<ConnetManager>
{
	public:
		//const TcpConnectionPtr& connection;
		ConnetManager();
		void add(const TcpConnectionPtr& con);
        //void add(uint32 uid,uint32 handler);

        void add(uint32 handler,GamePlayer *usr);


		void del(const TcpConnectionPtr& con);

		uint64 makeCid();
		TcpConnection* getConn(uint32 cid);
		GamePlayer *getPlayer(uint32 cid);
	private:
		friend class Singleton<ConnetManager>;
		//�ͻ���cid

		typedef map<uint32,TcpConnection*>  ConnetCidMap;
		ConnetCidMap m_cid_manager;

        typedef map<uint32,GamePlayer*> ConPLayerMap;
        ConPLayerMap m_con_player;

		SeqNumberAlloc *alloc;
};

#endif // _ECHO_SERVER_H_
