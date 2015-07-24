
#include "GamePackageManager.h"
#include "GameItem.h"
GamePlayerPackages::GamePlayerPackages(GamePlayer *player)
: m_uim(player),
m_commom_pack(&m_uim),
m_treasure_pack(&m_uim),
m_soul_pack(&m_uim),
m_equip_pack(player),
m_soul_equip_pack(&m_uim),
m_treasure_solt(player),
m_owner(player)
{

}
GamePlayerPackages::~GamePlayerPackages()
{

}

bool GamePlayerPackages::obtainItem(GameItem* &item, AddItemAction action)
{
	if(item)
	{
		switch(item->getBaseType())
		{
			case PackageType_Common:
				{
					return m_commom_pack.addItem(item,action);
				}
				break;
			case PackageType_Soul:
				{
					return m_soul_pack.addItem(item,action);
				}
				break;
			case PackageType_Treasure:
				{
					return m_treasure_pack.addItem(item,action);
				}
				break;
			default:
				return false;
		}
	}
	return true;
}

bool GamePlayerPackages::deleteItem(GameItem* &item, DelItemAction action)
{
	CheckCondition(item && m_owner, false);
    uint32 ret=0;
	if(m_commom_pack.removeItem(item,action,ret))
    {
        ItemCreator::destroyItem(item, m_owner, action);
    }

}

bool GamePlayerPackages::reduceItemNumByBaseID(uint32 baseid, uint32 num, DelItemAction action)
{
	vector<GameItem*>  dellist;
	GameItem* last_del;
	bool ret=false;
	for(ItemMap::iterator it = m_uim.m_item_manager.begin();it !=m_uim.m_item_manager.end();it++)
	{
		GameItem *entry=(*it).second;
		if(entry->getBaseID()==baseid)
		{
			if(num >= entry->m_data.num)
			{
				dellist.push_back(entry);
				num=num-entry->m_data.num;
				if(num == 0)
				{
					ret= true;
				}
			}
			else
			{
				last_del = entry;
				ret= true;
			}
		}
	}

	vector<GameItem*>::iterator iter = dellist.begin(), end = dellist.end();
	for(; iter != end; ++ iter)
	{
		deleteItem(*iter, action);
	}


	if(last_del)
	{
		last_del->subNumber(num, m_owner, action);
	}
}



uint32 GamePlayerPackages::unfixSolt(uint32 pos)
{
	CheckCondition(pos<TreasurePostion_Max,ERR_INNER);
	GameItem * item = m_treasure_solt.m_treausre[pos];
	CheckCondition(item,ERR_INNER);

	CheckCondition (m_commom_pack.checkLeftSpace(),ERR_VALID_GRIDS);

	if(m_commom_pack.moveItemIn(item))
	{
		m_treasure_solt.m_treausre[pos]=NULL;
		return ERR_SUCCESS;
	}
	return ERR_INNER;
}
uint32 GamePlayerPackages::onSolt(GameItem *item,uint8 pos)
{
	return m_treasure_solt.onEquip(item,pos);
}

uint32 GamePlayerPackages::onSolt(uint32 thisid,uint8 pos)
{
	return 1;
}

void GamePlayerPackages::fill(Json::Value &data)
{
	m_uim.fillDbData(data);
}
uint32 GamePlayerPackages::useItemByBaseId(uint32 thisid,uint32 num)
{
	GameItem *item = m_uim.getItemByThisID(thisid);
	CheckCondition(item, ERR_ITEM_NOTEXIST);

	return useItem(item,num);
}
uint32 GamePlayerPackages::useItem(GameItem* item,uint32 num)
{
	return 0;
}

