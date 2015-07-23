
#include "GameEquipImprove.h"
uint32 EquipImprove::strengthenEquip(uint8 pos)
{
	GameItem *item= m_owner->m_pack_manager.m_equip_pack.getEquip(pos);
	CheckCondition(item,ERR_PARAMS);
	if(cost())
	{
		item->updateEquipStrengthenLev();
		return ERR_SUCCESS;
	}
	return ERR_RESOURCE;
}

bool EquipImprove::cost()
{
	uint32 money = m_owner->getMoney(MoneyType_Money)
	GameItem *stone = m_owner->m_pack_manager.m_commom_pack.getItemByBaseID(100001);
	if(money>100&&stone&&stone->getItemNumber()>1)
	{
		m_owner->subMoney(MoneyType_Money,100,DelMoneyAction_EquipImprove);
		m_owner->m_pack_manager.reduceItemNumByBaseID(100001,1,DelItemAction_Improve);
		
		return true;
	}
	return false;
}

