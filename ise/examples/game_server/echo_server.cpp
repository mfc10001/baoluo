///////////////////////////////////////////////////////////////////////////////

#include "echo_server.h"
#include "game_core/ConfigManager.h"
#include "tools/CommonTools.h"

MySqlDatabase *m_db_conn=NULL;
IseBusiness* createIseBusinessObject()
{
    return new AppBusiness();
}

///////////////////////////////////////////////////////////////////////////////

const int RECV_TIMEOUT = 1000*5;  // ms

//-----------------------------------------------------------------------------
// 描述: 初始化 (失败则抛出异常)
//-----------------------------------------------------------------------------
void AppBusiness::initialize()
{
	try
	{
		addForwardPro(PROTOCOL_CREATE_CHAR_C);
		addForwardPro(PROTOCOL_ENTER_C);
		addForwardPro(PROTOCOL_CHAR_LIST_C);

		bool ret=ConfigManager::instance().loadAllFile();
		if(!ret)
		{
			throw(ret);
		}


		//链接DBserver
		recvBuf_.reset(new IoBuffer());

   		tcpClient_.reset(new TcpClient());
		tcpClient_->connect("127.0.0.1",22306);


	}
	catch(exception)
	{
		exit(1);
	}
    // nothing
}

//-----------------------------------------------------------------------------
// 描述: 结束化 (无论初始化是否有异常，结束时都会执行)
//-----------------------------------------------------------------------------
void AppBusiness::finalize()
{
    string msg = formatString("%s stoped.", getAppExeName(false).c_str());
    std::cout << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// 描述: 初始化成功之后
//-----------------------------------------------------------------------------
void AppBusiness::afterInit()
{
    string msg = formatString("%s started.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// 描述: 初始化失败
//-----------------------------------------------------------------------------
void AppBusiness::onInitFailed(Exception& e)
{
    string msg = formatString("fail to start %s.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------
// 描述: 初始化ISE配置信息
//-----------------------------------------------------------------------------
void AppBusiness::initIseOptions(IseOptions& options)
{
    // 设置服务器类型
    options.setServerType(ST_TCP);
    // 设置TCP服务器的总数
    options.setTcpServerCount(1);
    // 设置TCP服务端口号
    options.setTcpServerPort(10000);
    // 设置TCP事件循环的个数
    options.setTcpServerEventLoopCount(1);


	options.setAssistorThreadCount(1);

}

//-----------------------------------------------------------------------------
// 描述: 接受了一个新的TCP连接
//-----------------------------------------------------------------------------
void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    //string msg = "Welcome to the simple echo server, type 'quit' to exit.\r\n";

	ConnetManager::instance().add(connection);

    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}

//-----------------------------------------------------------------------------
// 描述: 断开了一个TCP连接
//-----------------------------------------------------------------------------
void AppBusiness::onTcpDisconnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpDisconnected (%s)", connection->getConnectionName().c_str());
	ConnetManager::instance().del(connection);
}

//-----------------------------------------------------------------------------
// 描述: TCP连接上的一个接收任务已完成
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

		uint32 n = value["type"].asUInt();
		if(isExist(n))
		{
			if(!value.isMember("data"))
			{
				return;
			}

			if(value["data"].isMember("cid"))
			{
				return;
			}
			value["data"]["cid"]=connection.get()->getSocket().getHandle();
			string rstr = value.toStyledString();

			char buff[MAX_SEND_BUFF];
			memset(buff,0,MAX_SEND_BUFF);
			uint16 len=rstr.length()+2;
			memcpy(buff,&len,sizeof(uint16));
			memcpy(buff+2,rstr.c_str(),rstr.length());

            if(tcpClient_->getConnection().sendBaseBuff(buff,len)<=0)
            {
				 logger().writeFmt("forward message falid : %s", msg.c_str());
			}
			return ;
		}
		else
		{
			msgProcess(connection,n,value["data"]);
		}

	}

    logger().writeFmt("Received message: %s", msg.c_str());
    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}

//-----------------------------------------------------------------------------
// 描述: TCP连接上的一个发送任务已完成
//-----------------------------------------------------------------------------
void AppBusiness::onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context)
{
    logger().writeStr("onTcpSendComplete");

   // connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT, RECV_TIMEOUT);
     //connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);
}



void AppBusiness::assistorThreadExecute(AssistorThread& assistorThread, int assistorIndex)
{
	if(assistorIndex==0)
	{
		while(true)
		{
			char revbuff[MAX_REV_BUFF];
			memset(revbuff,0,MAX_REV_BUFF);

            int recvBytes = tcpClient_->getConnection().recvBaseBuff(revbuff, MAX_REV_BUFF);

            if(recvBytes>0)
            {
                recvBuf_.get()->append(revbuff,recvBytes);
            }


            int readableBytes = recvBuf_.get()->getReadableBytes();
            while (readableBytes > 2)
            {
                const char *buffer = recvBuf_.get()->peek();
                uint16 len=0;
                memcpy(&len,buffer,sizeof(len));

                if (readableBytes >= len)
                {
                    string msg((char*)buffer+2, len-2);
                    Json::Reader reader;
                    Json::Value value;
                    if (reader.parse(msg, value))
                    {
                        if(value.isMember("type")&&value.isMember("code")&&value.isMember("data")&&value["data"].isMember("cid"))
                        {
                            uint32 type = value["type"].asUInt();

                            TcpConnection *ptr_con=ConnetManager::instance().getConn(value["data"]["cid"].asInt());
                            if(ptr_con)
                            {
                                innerMsgProcess(*ptr_con,type,value["data"],value["code"].asInt());
                            }
                        }
                    }

                    recvBuf_.get()->retrieve(len);
                    readableBytes = recvBuf_.get()->getReadableBytes();
                }
                else
                {
                    break;
                }


            }

			usleep(1000);
		}


	}

	/*
	else if(assistorIndex==1)
	{
		while(true)
		{
			int readableBytes = recvBuf_.get()->getReadableBytes();
			while (readableBytes > 2)
		    {
		    	const char *buffer = recvBuf_.get()->peek();
				uint16 len=0;
				memcpy(&len,buffer,sizeof(len));

		        if (readableBytes >= len)
		        {
				    string msg((char*)buffer+2, len-2);
					Json::Reader reader;
					Json::Value value;
                    if (reader.parse(msg, value))
                    {
                        string str = value["type"].asString();
                        int n = atoi(str.c_str());
                        if(n<1000)
                        {
                            string cid ="1";
                            int m = atoi(cid.c_str());
                            const TcpConnectionPtr *ptr_con=ConnetManager::instance().getConn(m);
                            if(ptr_con)
                            {
                                innerMsgProcess(*ptr_con,n,value["data"]);
                            }

                        }
                    }

		            recvBuf_.get()->retrieve(packetSize);

		        }
				else
				{
					break;
				}
		    }

			usleep(1000);
		}
	}
	*/
}

bool AppBusiness::isExist(uint32 pro)
{
	BaseSet::iterator it = forward_.find(pro);
	if(it==forward_.end())
	{
		return false;
	}
	return true;
}
void AppBusiness::addForwardPro(uint32 pro)
{
	forward_.insert(pro);
}


void  ConnetManager::add(const TcpConnectionPtr& con)
{
	TcpConnection *addr=con.get();
	int handler = addr->getSocket().getHandle();
    ConnetCidMap::iterator it=m_cid_manager.find(handler);
	if(it!=m_cid_manager.end())
	{
		return;
	}
	m_cid_manager[handler]=addr;
}

void ConnetManager::del(const TcpConnectionPtr& con)
{
    TcpConnection *addr=con.get();
    int handler = addr->getSocket().getHandle();
    ConnetCidMap::iterator it=m_cid_manager.find(handler);
	if(it==m_cid_manager.end())
	{
		return ;
	}
    m_cid_manager.erase(it);
}

uint64 ConnetManager::makeCid()
{
	return alloc->allocId();
}
TcpConnection* ConnetManager::getConn(uint32 cid)
{
	ConnetCidMap::iterator it=m_cid_manager.find(cid);
	if(it==m_cid_manager.end())
	{
		return NULL;
	}

	return (*it).second;
}

ConnetManager::ConnetManager()
{
    alloc=new SeqNumberAlloc(1000);
}

