
#include "GamePackageManager.h"
#include "GameItem.h"
GamePlayerPackages::GamePlayerPackages(GamePlayer *player)
: m_uim(player),
m_commom_pack(&m_uim),
m_treasure_pack(&m_uim),
m_soul_pack(&m_uim),
m_equip_pack(player),
m_soul_equip_pack(&m_uim),
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

