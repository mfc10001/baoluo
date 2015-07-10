#ifndef _ISE_ERR_H_
#define _ISE_ERR_H_
enum Protocol
{
	PROTOCOL_INVALID =100,
	PROTOCOL_TOKEN_C=1000,

	PROTOCOL_AUTH_CS=1001,
	
	PROTOCOL_LOGIN_CS=1002,

	PROTOCOL_CHAR_LIST_CS=1003,

	PROTOCOL_CREATE_CHAR_CS=1004,

};


enum ErrCode
{
	ERR_SUCCESS=0,
	ERR_INNER=1
	
	ERR_TOKEN_INVALID=5,
	ERR_TOKEN_TIME=6,
};
#endif

