
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

uint8 GameItem::getPackType()
{
	return m_data.pack_type;
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

uint32 GameItem::onUse(GamePlayer *player)
{
	CheckCondition(player,1);
	const ItemDataEntry* item =	ConfigManager::instance().getItemData(m_data.baseid);
	CheckCondition(item,1);
	switch(item->effect)
	{
		case 1:
			{
				//player->addMoney(MoneyType_Money,item->effect);
			}
			break;
		case 2:
			{
				player->addExp(item->effect);
			}
			break;
		case 3:
			{
				player->addBody(item->effect);
			}
			break;
	}
}

uint32 GameItem::serialize(uint8 *out)
{

	CheckCondition(out, 0);
	uint32 num = 0;
	char buffer[PLAYER_SAVE_DATA_MAX_SIZE];
	uint32 len = PLAYER_SAVE_DATA_MAX_SIZE;
	bzero(buffer, len);

	SerializeDataMember* next = (SerializeDataMember*)(buffer);

	bcopy(&m_data,next->data,sizeof(m_data));
	next->type=0;
	next->num=sizeof(m_data);
	num+=next->allSize();
	next=(SerializeDataMember*)(&next->data[next->num]);

	memcpy(buffer,out,num);
	return num;
}
void GameItem::unserialize(uint8* in_data)
{
	bcopy(in->data,&m_data,sizeof(m_data));
}


