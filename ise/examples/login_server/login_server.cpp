///////////////////////////////////////////////////////////////////////////////

#include "login_server.h"


//-----------------------------------------------------------------------------
MySqlDatabase *m_db_conn=NULL;
TcpClient *tcpClient_ = NULL;


IseBusiness* createIseBusinessObject()
{
    return new AppBusiness();
}

///////////////////////////////////////////////////////////////////////////////

void AppBusiness::initMessage()
{
    string line;
    for (int i = 33; i < 127; ++i)
        line.push_back(char(i));
    line += line;

    message_.clear();
    for (size_t i = 0; i < 127-33; ++i)
        message_ += line.substr(i, 72) + '\n';
}

//-----------------------------------------------------------------------------

void AppBusiness::initialize()
{
    initMessage();
    transferredBytes_ = 0;

	try
	{
        m_db_conn=new MySqlDatabase();
        DbConnParams *param=m_db_conn->getDbConnParams();
        param->setHostName("192.168.18.147");
        param->setUserName("root");
        param->setPassword("123456");
        param->setDbName("baoluo_account");
        param->setPort(3306);

        MySqlConnection *dbconn = static_cast<MySqlConnection *> (m_db_conn->createDbConnection());
        dbconn->doConnect();


        char buff[BUFFLEN];
		MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());
		sprintf(buff,"select * from serverinfo where GameID=1");
        query->setSql(buff);
        MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
		while(!res->isEmpty() && res->next())
		{
			MySqlField* game_id = static_cast<MySqlField *> (res->getFields("ID"));
			MySqlField* s_name = static_cast<MySqlField *> (res->getFields("ServerName"));
			MySqlField* addr = static_cast<MySqlField *> (res->getFields("Address"));
			MySqlField* port = static_cast<MySqlField *> (res->getFields("Port"));

			sevreinfo pinfo;
			pinfo.sid=game_id->asInteger();
			pinfo.name=s_name->asString();
			pinfo.addr=addr->asString();
			pinfo.port=port->asInteger();
			server_manager_[pinfo.sid]=pinfo;
<<<<<<< HEAD:ise/examples/login_server/login_server.cpp

			if(!tcpClient_)
			{
				tcpClient_=new TcpClient();
				
				tcpClient_->connect(pinfo.addr.c_str(),pinfo.port);
			}

=======
>>>>>>> f8979d97bb98bb5776235788a6159a15a89e8baf:ise/examples/login_server/login_server.cpp

		}
		delete res;
		res = NULL;

<<<<<<< HEAD:ise/examples/login_server/login_server.cpp



=======
>>>>>>> f8979d97bb98bb5776235788a6159a15a89e8baf:ise/examples/login_server/login_server.cpp
	}
    catch(exception)
    {
        exit(1);
    }
}

//-----------------------------------------------------------------------------

void AppBusiness::finalize()
{
    string msg = formatString("%s stoped.", getAppExeName(false).c_str());
    std::cout << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------

void AppBusiness::afterInit()
{
    string msg = formatString("%s started.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------

void AppBusiness::onInitFailed(Exception& e)
{
    string msg = formatString("fail to start %s.", getAppExeName(false).c_str());
    std::cout << std::endl << msg << std::endl;
    logger().writeStr(msg);
}

//-----------------------------------------------------------------------------

void AppBusiness::initIseOptions(IseOptions& options)
{
    options.setServerType(ST_TCP);
    options.setTcpServerCount(1);
    options.setTcpServerPort(10003);
    options.setTcpServerEventLoopCount(1);

	options.setAssistorThreadCount(1);
}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpConnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpConnected (%s) (ConnCount: %d)",
        connection->getPeerAddr().getDisplayStr().c_str(),
        connection->getServerConnCount());

    connection->setNoDelay(true);

    connection->recv();
    connection->send(message_.c_str(), message_.length());
}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpDisconnected(const TcpConnectionPtr& connection)
{
    logger().writeFmt("onTcpDisconnected (%s)", connection->getConnectionName().c_str());
}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpRecvComplete(const TcpConnectionPtr& connection, void *packetBuffer,
    int packetSize, const Context& context)
{
    logger().writeFmt("[%s] Discarded %u bytes.",
        connection->getConnectionName().c_str(), packetSize);


	//logger().writeStr("onTcpRecvComplete");

	 char *dataptr=(char*)packetBuffer;

	 string msg((char*)dataptr+2, packetSize-2);

	 Json::Reader reader;
	 Json::Value value;
	if (reader.parse(msg, value))
	{
		uint32 n = value["type"].asUInt();
		msgProcess(connection,n,value["data"]);
	}


    connection->recv(SELF_PACKET_SPLITTER, EMPTY_CONTEXT);

}

//-----------------------------------------------------------------------------

void AppBusiness::onTcpSendComplete(const TcpConnectionPtr& connection, const Context& context)
{
    transferredBytes_ += message_.length();
    connection->send(message_.c_str(), message_.length());
}

bool AppBusiness::msgProcess(const TcpConnectionPtr& connection,uint32 type,Json::Value &arrayObj)
{
	uint32 err=1;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=PROTOCOL_INVALID;;
    char buff[BUFFLEN];
	switch(type)
	{
		case PROTOCOL_REGISTER_C:
            {
				rNo =PROTOCOL_SERVER_ADDR_C;
				string PassportID = arrayObj["PassportID"].asString();
                string PassporPwd = arrayObj["PassporPwd"].asString();
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());
				sprintf(buff,"select count(*) as num from snsuserinfo where PassportID=%s",PassportID.c_str());
                query->setSql(buff);
                MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
				if(!res->isEmpty() && res->next())
				{
					MySqlField* num = static_cast<MySqlField *> (res->getFields("num"));
					if(num->asInteger()>0)
					{
						break;
					}
					delete res;
					res = NULL;

					memset(buff,0,BUFFLEN);
					sprintf(buff,"insert into snsuserinfo (PassportID,PassportPwd) values ('%s','%s');  ",PassportID.c_str(),PassporPwd.c_str());
					query->setSql(buff);

					try
					{
						query->execute();
						uint64 aid = query->getLastInsertId();
						rData["aid"]=(uint32)aid;
						delete res;
						res = NULL;
						err=ERR_SUCCESS;
					}
					catch(Exception)
					{
						break;
					}
				}
            }
			return true;
		case PROTOCOL_LOGIN_C:
            {
				rNo =PROTOCOL_SERVER_ADDR_S;
				string PassportID = arrayObj["PassportID"].asString();
                string PassporPwd = arrayObj["PassporPwd"].asString();
				MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());
				sprintf(buff,"select AID,PassportPwd from snsuserinfo where PassportID='%s'",PassportID.c_str());
                query->setSql(buff);
                MySqlDataSet *res=static_cast<MySqlDataSet *>(query->query());
				if(!res->isEmpty() && res->next())
				{
					MySqlField* pwd = static_cast<MySqlField *> (res->getFields("PassporPwd"));
					if(strcmp(PassporPwd.c_str(),pwd->asString().c_str())==0)
					{
						err=ERR_SUCCESS;

						rData["token"]="1111";
					}
					else
					{
						err=ERR_PWD;
					}
				}
				else
				{
					err=ERR_UNREGISTER;
				}


                rNo=PROTOCOL_AUTH_S;

            }
			break;
		case PROTOCOL_SERVERLIST_C:
			{
				for(map<uint32 ,sevreinfo> ::iterator it =server_manager_.begin();it!=server_manager_.end();it++)
				{
					rData["ID"]=(*it).second.sid;
					//rData["addr"]=(*it).second.addr;
					//rData["port"]=(*it).second.port;
					rData["name"]=(*it).second.name;
				}
				rNo=PROTOCOL_SERVERLIST_S;
				err=ERR_SUCCESS;
			}

			break;
		case PROTOCOL_SERVER_ADDR_C:
			{
				rNo = PROTOCOL_SERVER_ADDR_S;
				uint32 id = arrayObj["ID"].asUInt();
				map<uint32 ,sevreinfo> ::iterator it=server_manager_.find(id);
				if(it==server_manager_.end())
				{
					err=ERR_NONE_SERVER;
					break;
				}
<<<<<<< HEAD:ise/examples/login_server/login_server.cpp
					{
						Json::Value rValueg,rDatag;
						rDatag["token"]="1111";
						rValueg["code"]=err;
						rValueg["type"]=rNo;
						rValueg["data"]=rDatag;
						string str = rValueg.toStyledString();
						if(tcpClient_->getConnection().sendBaseBuff(buff,len)<=0)
						{
							 logger().writeFmt("forward message falid : %s", rstr.c_str());
						}
					}
=======
>>>>>>> f8979d97bb98bb5776235788a6159a15a89e8baf:ise/examples/login_server/login_server.cpp
				rData["addr"]=(*it).second.addr;
				rData["port"]=(*it).second.port;
				err=ERR_SUCCESS;
				
			}
			break;
		default:
			return false;
	}


	rValue["code"]=err;
	rValue["type"]=rNo;
	rValue["data"]=rData;
	string str = rValue.toStyledString();

	char buff_send[MAX_SEND_BUFF];
	memset(buff_send,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff_send,&len,sizeof(uint16));
	memcpy(buff_send+2,str.c_str(),str.length());

	connection->send(buff_send,len);
}


void AppBusiness::assistorThreadExecute(AssistorThread& assistorThread, int assistorIndex)
{

}


