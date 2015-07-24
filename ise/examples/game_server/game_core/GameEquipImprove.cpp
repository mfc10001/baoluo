
#include "GameEquipImprove.h"
#include "GamePlayer.h"
#include "GameItem.h"

EquipImprove::EquipImprove(GamePlayer *player):
m_owner(player)
{

}
EquipImprove::~EquipImprove()
{

}
uint32 EquipImprove::strengthenEquip(uint32 thisid)
{

	GameItem *item= GlobalItemManager::instance().getItemByThisID(thisid);
	CheckCondition(item,ERR_PARAMS);

	uint32 ret = cost(item);
	if(ret!=ERR_SUCCESS)
	{
		item->updateEquipStrengthenLev();
		return ERR_SUCCESS;
	}
	return ret;
}

uint32  EquipImprove::cost(GameItem* item)
{
	uint32 coststonenum=0;
	uint32 costmoney=100;

	uint32 money = m_owner->getMoney(MoneyType_Money);

	if(coststonenum != 0)
	{
		GameItem *stone = m_owner->m_pack_manager.m_commom_pack.getItemByBaseID(100001);
		CheckCondition(stone,ERR_STONE);
		CheckCondition(stone->getItemNumber()>coststonenum,ERR_STONE);
	}

	CheckCondition(money>=costmoney,ERR_MONEY);


	m_owner->subMoney(MoneyType_Money,costmoney,DelMoneyAction_EquipImprove);
	if(coststonenum != 0)
	{
		m_owner->m_pack_manager.reduceItemNumByBaseID(100001,coststonenum,DelItemAction_Improve);
	}
	return ERR_SUCCESS;

}

