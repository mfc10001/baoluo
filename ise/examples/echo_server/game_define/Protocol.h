#ifndef _ISE_ERR_H_
#define _ISE_ERR_H_
#include <map>
#include <set>
using namespace std;
enum Protocol
{
	PROTOCOL_INVALID =1,
	//inner msg  2-999




	PROTOCOL_TOKEN_C=900,
	//client msg

	
	PROTOCOL_AUTH_C=1000,
	PROTOCOL_AUTH_S,

	PROTOCOL_CREATE_CHAR_C,
	PROTOCOL_CREATE_CHAR_S,

	PROTOCOL_ENTER_C,
	PROTOCOL_ENTER_S,
	
	PROTOCOL_CHAR_LIST_C,
	PROTOCOL_CHAR_LIST_S,
	
	
	

};


enum ErrCode
{
	ERR_SUCCESS=0,
	ERR_INNER=1,

	ERR_TOKEN_INVALID=5,
	ERR_TOKEN_TIME=6,

	ERR_EXIST_ROLE=7,
};


#define MAX_SEND_BUFF 4086
#define MAX_REV_BUFF 4096
const uint16 BUFFLEN  = 512;


typedef map<uint32,uint32>  BaseMap;
typedef set<uint32> BaseSet;

#endif

