///////////////////////////////////////////////////////////////////////////////

#include "echo_server.h"
#include "game_core/ConfigManager.h"
#include "tools/CommonTools.h"
#include "game_define/Protocol.h"
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
		addForwardPro(PROTOCOL_CREATE_CHAR_CS);

		bool ret=ConfigManager::instance().loadAllFile();
		if(!ret)
		{
			throw(ret);
		}


		//����DBserver
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


	options.setAssistorThreadCount(1);

}

//-----------------------------------------------------------------------------
// ����: ������һ���µ�TCP����
//-----------------------------------------------------------------------------
void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    //string msg = "Welcome to the simple echo server, type 'quit' to exit.\r\n";

	uint32 cid=ConnetManager::instance().add(connection);
	Json::Value rValue;
	rValue["cid"]=cid;
	string str = rValue.toStyledString();
	char buff[MAX_SEND_BUFF];
	memset(buff,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff,&len,sizeof(uint16));
	memcpy(buff+2,str.c_str(),str.length());
	connection->send(buff,len);

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
		if(isExist(n))
		{
            if(tcpClient_->getConnection().sendBaseBuff(dataptr,packetSize)<=0)
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

					recvBuf_.get()->retrieve(len);

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


uint32  ConnetManager::add(const TcpConnectionPtr& con)
{
	uint32 cid=makeCid();
    ConnetManagerMap::iterator it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return 0;
	}
	m_con_manager[cid]=&con;
	return cid;
}
void ConnetManager::del(uint32 cid)
{
	ConnetManagerMap::iterator it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return;
	}
	m_con_manager.erase(it);
}

uint64 ConnetManager::makeCid()
{
	return alloc.allocId();
}
const TcpConnectionPtr* ConnetManager::getConn(uint32 cid)
{
	ConnetManagerMap::iterator it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return NULL;
	}

	return (*it).second;
}

ConnetManager::ConnetManager()
{
	alloc.SeqNumberAlloc(1000);
}

