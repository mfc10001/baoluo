#ifndef _ISE_ENTRYBASE_H_
#define _ISE_ENTRYBASE_H_
#include "ise/main/ise.h"
#include "Protocol.h"

enum PlayerAttr
{
	PlayerAttr_physicsAttack=0,
	PlayerAttr_magicAttack,
	PlayerAttr_barmor,
	PlayerAttr_bresistance,
	PlayerAttr_hp,
	PlayerAttr_hit,
	PlayerAttr_dodge,
	PlayerAttr_crit,
	PlayerAttr_opposeCrit,
	PlayerAttr_physicsAttackz,
	PlayerAttr_magicAttackz,
	PlayerAttr_barmorz,
	PlayerAttr_bresistancez,
	PlayerAttr_hpz,
	PlayerAttr_hitz,
	PlayerAttr_dodgez,
	PlayerAttr_critz,
	PlayerAttr_opposeCritz,



	PlayerAttr_Max=48,
};

enum MoneyType
{
	MoneyType_Money					= 0,	///< 黄金
	MoneyType_Diamond				= 1,	///< 钻石
	MoneyType_Medal                 = 2,    ///< 勋章
	MoneyType_CashGift 			    = 3,	///< 礼金   //改为绑定钻石
	MoneyType_Crystal 				= 4,	///< 光晶
	MoneyType_FightSpirit 	        = 5,	///< 战魂
    MoneyType_End ,
};

inline bool  isMoneyTypeValid(MoneyType type)
{
	return MoneyType_Money <= type && type < MoneyType_End;
}
static const uint64 MONEY_LIMIT	= 999999999;

enum AddMoneyAction
{
	AddMoneyAction_None                 = 0,
	AddMoneyAction_EquipImprove			= 1,

	AddMoneyAction_Max
};

inline const char *getAddMoneyActionStr(uint8 act)
{
	static char *AddMoneyActionName[] =
	{
        "use"
	};
	return act < AddMoneyAction_Max ? AddMoneyActionName[act] : "异常的金钱添加操作类型";
}

enum DelMoneyAction
{
	DelMoneyAction_None                 = 0,    ///< 未知

	DelMoneyAction_EquipImprove			= 1,
	DelMoneyAction_Max,
};

inline const char *getDelMoneyActionStr(uint8 act)
{
	static char *DelMoneyActionName[] =
	{
        "use"
	};
	return act < DelMoneyAction_Max ? DelMoneyActionName[act] : "异常的删除金钱类型";
}


struct PlayerBaseAttr
{
    PlayerBaseAttr()
    {
        memset(this,0,sizeof(*this));
    }
	char name[MAX_NAME_SIZE];
	uint32 role;
	uint8 init_flag;

	uint16 level;
	uint32 exp;

};

typedef boost::function<void ()> PlayerLevelHandlerCallback;


class GameEntry :public Entry
{
    public:
	virtual uint32 getRole(){return m_base_attr.role;};
	PlayerBaseAttr m_base_attr;
};

#endif
