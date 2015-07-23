#include "GameItemManager.h"
#include "../game_define/BaseType.h"
#include "GameItem.h"


GameItemManager::GameItemManager(GamePlayer *user)
:owner(user)
{

}
GameItemManager::~GameItemManager()
{

}

bool GameItemManager::addItem(GameItem* item)
{
    return false;
}
void GameItemManager::removeItem(GameItem* item)
{

}


GamePlayer *GameItemManager::getOwner()
{
    return owner;
}

void  GameItemManager::fillDbData(Json::Value &arrayObj)
{
	for(ItemMap::iterator it = m_item_manager.begin();it != m_item_manager.end();it++)
	{
		GameItem *entry = (*it).second;

		Json::Value temp;
		temp["thisid"]=entry->m_data.thisid;
		temp["baseid"]=entry->m_data.baseid;
		temp["num"]=entry->m_data.num;
		temp["base_type"]=entry->m_data.base_type;
		if(entry->m_data.base_type == ItemType_Equip)
		{
			temp["Strengthen"]=entry->m_data.Strengthen;
			temp["Hole1"]=entry->m_data.Hole1;
			temp["Hole2"]=entry->m_data.Hole2;
			temp["Hole3"]=entry->m_data.Hole3;		
			temp["Hole4"]=entry->m_data.Hole4;		
		}
		arrayObj.append(temp);
	}
}

void GameItemManager::save()
{
/*
	Json::Value data;
	data["type"]=INNER_SAVE_PACKAGE_DATA;
	fillDbData(data["data"]);
	AppBusiness::sendToDb(data);
	*/
}


//////
GameItem* ItemCreator::createItem(const ItemDataEntry *base, uint32 num, uint32 src_id, const char* src_name, const char *desc, AddItemAction action,  GamePlayer *owner)
{
	GameItem* item = new GameItem();
	CheckCondition(item, NULL);

	item->m_base_data = base;
	item->m_data.baseid = base->id;
	strncpy(item->name, base->name, MAX_NAMESIZE);
	item->m_data.num = 1;//((item->m_base_data->max_num >= num) ? num : 1);
	item->generateThisID();
	item->m_data.create_time = Timestamp::now().epochMilliseconds();


	if(!GlobalItemManager::instance().addItem(item))
	{
		DELETE_VALUE(item);
		return NULL;
	}

	return item;
}
bool ItemCreator::autoUnionCreateItem(uint32 baseid, uint32 num, GamePlayer *owner, AddItemAction action)
{
	CheckCondition(owner, false);

	const ItemDataEntry* base_data = ConfigManager::instance().getItemData(baseid);
	//LogCheckCondition(base_data, false, "获取道具属性表失败 baseid:%u, action:%u", baseid, action);
	CheckCondition(base_data, false);


	GameItem* item = ItemCreator::createItem(base_data, num, owner->getEntryID(), owner->getEntryName(), getAddItemActionStr(action), action, owner);
	if(owner->m_pack_manager.obtainItem(item, action))
	{

	}
	else
	{
		destroyItem(item,  owner, DelItemAction_CreateAddToPackageFail);
	}

	return true;
}

void ItemCreator::destroyItem(GameItem* &item, GamePlayer* owner, DelItemAction action)
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
		return;
	}
	m_item_manager.erase(it);
}

