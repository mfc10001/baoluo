///////////////////////////////////////////////////////////////////////////////

#include "echo_server.h"
#include "game_core/ConfigManager.h"
#include "ise/ext/dbi/mysql/ise_dbi_mysql.h"
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
		bool ret=ConfigManager::instance().loadAllFile();
		if(!ret)
		{
			throw(ret);
		}

		m_db_conn=new MySqlDatabase();

		DbConnParams *param=m_db_conn->getDbConnParams();
		param->setHostName("192.168.18.147");
		param->setUserName("root");
		param->setPassword("123456");
		param->setDbName("baoluo_zs");
		param->setPort(3306);

		MySqlConnection *dbconn = static_cast<MySqlConnection *> (m_db_conn->createDbConnection());
		dbconn->doConnect();
		//链接DBserver
		recvBuf_.reset(new IoBuffer(1024));
		
   		tcpClient_.reset(new BaseTcpClient());
		tcpClient_->connect("127.0.0.1",22306)

		
	}
	catch(bool)
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

	uint32 cid=ConnetMangaer.add(connection);
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
// 描述: 断开了一个TCP连接
//-----------------------------------------------------------------------------
void AppBusiness::onTcpDisconnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpDisconnected (%s)", connection->getConnectionName().c_str());
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
		string str = value["type"].asString();
		int n = atoi(str.c_str());
		if(n<1000)
		{
			string cid = value["cid"].asString();
			int m = atoi(cid.c_str());
			const TcpConnectionPtr * ptr_con=ConnetMangaer.instance().getConn(m);
			if(ptr_con)
			{
				innerMsgProcess(ptr_con,n,value["data"]);
			}
			
		}
		else
		{
			msgProcess(connection,n,value["data"]);

		}


	}
/*
    msg = trimString(msg);
    if (msg == "quit")
        connection->disconnect();
    else
        connection->send((char*)packetBuffer, packetSize);
*/
    logger().writeFmt("Received message: %s", msg.c_str());
}

//-----------------------------------------------------------------------------
// 描述: TCP连接上的一个发送任务已完成
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
			uint32 readindex=0;
			uint32 writeindex=0;
			uint16 length=0;
			
			char revbuff[MAX_REV_BUFF];
			memset(revbuff,0,MAX_REV_BUFF);
            int recvBytes = tcpClient_->recvBuffer(revbuff, MAX_REV_BUFF);
			if(recvBytes>0)
			{
				recvBuf_.append(revbuff,recvBytes);
			}
			
			usleep(1000);
		}
		

	}
	else if(assistorIndex==1)
	{
		while(true)
		{
			int readableBytes = recvBuf_.getReadableBytes();
			while (readableBytes > 2)
		    {
		    	const char *buffer = recvBuf_.peek();
		        int packetSize = 0;
				uint16 len=0;
				memcpy(len,buffer,sizeof(len));

		        if (readableBytes >= len)
		        {
		        	char *dataptr=(char*)buffer;
				    string msg((char*)dataptr+2, packetSize-2);
					//Json::Reader reader;
					//Json::Value value;
				
		            recvBuf_.retrieve(packetSize);
	
		        }
				else
				{
					break;
				}
		    }
			
			usleep(1000);
		}
	}
}



uint32  ConnetMangaer::add(const TcpConnectionPtr& con)
{
	uint32 cid=makeCid();
	ConnetManagerMap::it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return 0;
	}
	m_con_manager[cid]=con;
}
void ConnetMangaer::del(uint32 cid)
{
	ConnetManagerMap::it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return;
	}
	m_con_manager.erase(it);
}

uint32 ConnetMangaer::makeCid()
{
	return 0;
}
const TcpConnectionPtr* ConnetMangaer::getConn(uint32 cid)
{
	ConnetManagerMap::it=m_con_manager.find(cid);
	if(it==m_con_manager.end())
	{
		return null;
	}

	return &(*it).second;
}


