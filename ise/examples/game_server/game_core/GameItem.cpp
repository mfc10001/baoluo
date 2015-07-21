
#include "GameItem.h"
void GameItem::generateThisID()
{
	int64 id = (randBetween(0, 1) ? randBetween(-1000, 0x80000000) : randBetween(1000, 0x7FFFFFFE));
	m_data.thisid = id;
}


uint8 GameItem::getBaseType()
{
	return m_base_data.type;
}

uint32 GameItem::getBaseID()
{
	return m_data.baseid;
}


bool GameItem::incNumber(uint32 num, GamePlayer *player, AddItemAction act)
{
	if(m_base_data->max_num ==0)
	{
		m_data.num += num;	
	}
	/*
	if(num + m_data.num <= m_base_data->max_num)
	{
		m_data.num += num;		
	}
	*/
	return true;
}
bool GameItem::subNumber(uint32 num, GamePlayer *player, Cmd::DelItemAction act)
{
	CheckCondition(m_data.num >= num, false);

	m_data.num -= num;
	return true;
}

uint32 GameItem::getItemNumber()
{
	return m_data.num;
}

