#ifndef _ISE_ERR_H_
#define _ISE_ERR_H_
#include <map>
#include <set>
using namespace std;
enum Protocol
{
	PROTOCOL_INVALID =1,



	//login

	PROTOCOL_REGISTER_C = 100,
	PROTOCOL_REGISTER_S ,
	PROTOCOL_LOGIN_C,
	PROTOCOL_LOGIN_S,
	PROTOCOL_SERVERLIST_C,
	PROTOCOL_SERVERLIST_S,
	PROTOCOL_SERVER_ADDR_C,
	PROTOCOL_SERVER_ADDR_S,

	//inner msg  200-500
	INNER_SAVE_DATA =200,


	PROTOCOL_TOKEN_C=900,
	//client msg


	PROTOCOL_AUTH_C=1000,
	PROTOCOL_AUTH_S,

	PROTOCOL_CREATE_CHAR_C,
	PROTOCOL_CREATE_CHAR_S,

	PROTOCOL_ENTER_C,
	PROTOCOL_ENTER_S,

	PROTOCOL_CHAR_LIST_C,
	PROTOCOL_CHAR_LIST_S


};


enum ErrCode
{
	ERR_SUCCESS=0,
	ERR_INNER=1,//�ڲ�����
	//login
	ERR_PWD=3,//�������
	ERR_UNREGISTER=4,//δע��
	ERR_NONE_SERVER=5,//û���ҵ����Ϸ�������ַ

    //game
	ERR_TOKEN_INVALID=20,//��Чtoken
	ERR_TOKEN_TIME,//token����
	ERR_EXIST_ROLE,//�Ѿ����ڽ�ɫ
	ERR_TOKEN_NULL,//û���ҵ�token
	ERR_EXIST_AL_LOGIN,//�Ѿ���½


	ERR_CHAR_EXIST=30//��ɫ
};


#define MAX_SEND_BUFF 4086
#define MAX_REV_BUFF 4096
const uint16 BUFFLEN  = 512;
const uint16 RECV_TIMEOUT = 1000*5;  // ms
const uint16 MAX_NAMESIZE =48;

typedef map<uint32,uint32>  BaseMap;
typedef set<uint32> BaseSet;

#endif

