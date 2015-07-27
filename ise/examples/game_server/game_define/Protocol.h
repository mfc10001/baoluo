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
	INNER_SAVE_PLAYER_BASE_DATA =200,
	INNER_SAVE_PACKAGE_DATA		=201,

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

	PROTOCOL_CHAR_MONEY_S=1009,

	PROTOCOL_EQUIP_IMPROVE_C=1010,
	PROTOCOL_EQUIP_IMPROVE_S=1011,
	PROTOCOL_EQUIP_TREASURE_C=1012,

	PROTOCOL_EQUIP_TREASURE_S=1013,
	PROTOCOL_EQUIP_UNFIX_TREASURE_C=1014,
	PROTOCOL_EQUIP_UNFIX_TREASURE_S=1015,

	PROTOCOL_PACK_LIST_C=1016,
	PROTOCOL_PACK_LIST_S=1017,

	PROTOCOL_ITEM_USE_C=1018,
	PROTOCOL_ITEM_USE_S=1019,

	PROTOCOL_STORE_BUY_C=1100,
	PROTOCOL_STORE_BUY_S=1101,

};


enum ErrCode
{
	ERR_SUCCESS=0,
	ERR_INNER=1,//内部错误
	//login
	ERR_PWD=3,//密码错误
	ERR_UNREGISTER=4,//未注册
	ERR_NONE_SERVER=5,//没有找到酚蜗服务器地址

    //game
	ERR_TOKEN_INVALID=20,//无效token
	ERR_TOKEN_TIME,//token过期
	ERR_EXIST_ROLE,//已经存在角色
	ERR_TOKEN_NULL,//没有找到token
	ERR_EXIST_AL_LOGIN,//已经登陆

	ERR_CHAR_EXIST=30,//角色


	ERR_PARAMS=40,//参数错误

	ERR_MONEY =41,
	ERR_STONE=42,


	ERR_POSITION=43,//位置不可用

	ERR_VALID_GRIDS=44,

	ERR_ITEM_NOTEXIST = 45,

	ERR_ITEM_NULL = 46,

	ERR_DIAMOND_LACK = 47,

	ERR_PACK_NULL = 48,



	ERR_PACK_POS_EXIST=70,//已经存在不用移动
};


#define MAX_SEND_BUFF 4086
#define MAX_REV_BUFF 4096

#define MAX_NAME_SIZE 50
#define MAX_SOUL_PACKAGE_SOLT  6
const uint16 BUFFLEN  = 2048;
const uint16 RECV_TIMEOUT = 1000*5;  // ms
//const uint16 MAX_NAMESIZE =48;
#define MAX_NAMESIZE 48
typedef map<uint32,uint32>  BaseMap;
typedef set<uint32> BaseSet;


class GameItem;
typedef map<uint32 , GameItem*> ItemMap;

#endif

