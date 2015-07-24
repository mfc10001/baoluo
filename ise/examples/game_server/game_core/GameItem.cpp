
#include "GameItem.h"
#include "GamePlayer.h"

void GameItem::generateThisID()
{
	id = (getRandom(0, 1) ? getRandom(-1000, 0x80000000) : getRandom(1000, 0x7FFFFFFE));
	m_data.thisid = id;
}

void GameItem::updateEquipStrengthenLev()
{
    m_data.equip_attr[EquipAttrGeneType_Strengthen]+=1;
}
uint8 GameItem::getBaseType()
{
	return m_data.base_type;
}

uint32 GameItem::getBaseID()
{
	return m_data.baseid;
}


bool GameItem::incNumber(uint32 num, GamePlayer *player, AddItemAction act)
{
    m_data.num += num;

	/*
	if(num + m_data.num <= m_base_data->max_num)
	{
		m_data.num += num;
	}
	*/
	return true;
}
bool GameItem::subNumber(uint32 num, GamePlayer *player, DelItemAction act)
{
	CheckCondition(m_data.num >= num, false);

	m_data.num -= num;
	return true;
}

uint32 GameItem::getItemNumber()
{
	return m_data.num;
}



