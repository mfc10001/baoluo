#include "GameItemManager.h"

bool addItem(GameItem* item)
{
}
void removeItem(GameItem* item)
{
	
}


GameItem* ItemCreator::createItem(const ItemDataEntry *base, uint32 num, uint32 src_id, const char* src_name, const char *desc, Cmd::AddItemAction action,  GamePlayer *owner = NULL);
{
	GameItem* item = new GameItem();
	CheckCondition(item, NULL);

	item->m_base_data = base;
	item->m_data.baseid = base->id;
	strncpy(item->name, base->name, MAX_NAMESIZE);
	item->m_data.num = 1;//((item->m_base_data->max_num >= num) ? num : 1);
	item->generateThisID();
	item->m_data.create_time = Timestamp::now();


	if(!GlobalItemManager::getInstance().addItem(item))
	{
		DELETE_VALUE(item);
		return NULL;
	}

	return item;
}
bool ItemCreator::autoUnionCreateItem(uint32 baseid, uint32 num, GamePlayer *owner, Cmd::AddItemAction action)
{
	CheckCondition(owner, false);

	const ItemDataEntry* base_data = ItemDataEntryManager::getInstance().getTableByID(baseid);
	//LogCheckCondition(base_data, false, "获取道具属性表失败 baseid:%u, action:%u", baseid, action);
	CheckCondition(base_data, false);


	GameItem* item = ItemCreator::createItem(base_data, num, owner->id, owner->name, getAddItemActionStr(action), action, owner);
	if(owner->m_packages.obtainItem(item, action))
	{
		
	}
	else
	{
		destroyItem(item,  owner, DelItemAction_CreateAddToPackageFail);
	}
}

void ItemCreator::destroyItem(GameItem* &item, GamePlayer* owner, DelItemAction action);
{
	CheckConditionVoid(item);
	DELETE_VALUE(item);
}



bool GlobalItemManager::addItem(GameItem* item)
{
	CheckCondition(item, false);
	
	GameItem* temp_item = getItemByThisID(item->id);
	if(!temp_item)
	{
		return addEntry(item);
	}
	while(true)
	{
		item->generateThisID();
		if(addEntry(item))
		{
			return true;
		}
	}
}

bool GlobalItemManager::addEntry(GameItem* item)
{
	GameItem* temp_item = getItemByThisID(item->id);
	if(temp_item)
	{
		return false;
	}

	m_item_manager.insert(std::make_pair(item->id, item));
	return true;
}

GameItem* GlobalItemManager::getItemByThisID(uint32 thisid)
{
	ItemMap::iterator it = m_item_manager.find(thisid);
	if(it == m_item_manager.end())
	{
		return NULL;
	}
	return (*it).second;
}
void GlobalItemManager::removeItem(GameItem* item)
{
	
}
void GlobalItemManager::removeItem(uint32 thisid)
{
	ItemMap::iterator it = m_item_manager.find(thisid);
	if(it == m_item_manager.end())
	{
		return NULL;
	}
	m_item_manager.erase(it);
}

