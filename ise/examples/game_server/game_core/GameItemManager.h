#ifndef _ISE_GAMEITEMMANAGER_H_
#define _ISE_GAMEITEMMANAGER_H_


#include "ise/main/ise.h"

#include "GameItem.h"
class GameItemManager :public Singleton<GameItemManager>
{

	bool addItem(GameItem* item);
	void removeItem(GameItem* item);

    friend class Singleton<GameItemManager>;

	typedef map<uint32 , GameItem*> ItemMap;
	ItemMap m_item_manager;

};

struct ItemCreator
{
	static GameItem* createItem(const ItemDataEntry *base, uint32 num, uint32 src_id, const char* src_name, const char *desc, Cmd::AddItemAction action,  GamePlayer *owner = NULL, Cmd::ItemQualityType quality = Cmd::ItemQualityType_None);
	static bool autoUnionCreateItem(uint32 baseid, uint32 num, GamePlayer *owner, Cmd::AddItemAction action, uint16 bind_mask = 0, Cmd::ItemQualityType quality = Cmd::ItemQualityType_None, uint8 emoney_mask = 0);
	static void destroyItem(GameItem* &item, uint32 oper_id, const char* oper_name, uint32 owner_id, const char* owner_name, GamePlayer* owner, Cmd::DelItemAction action);
}



class GlobalItemManager :public Singleton<GlobalItemManager>
{
	private:
		friend class Singleton<GlobalItemManager>;
		GlobalItemManager();
		~GlobalItemManager();

	public:
		bool addItem(GameItem* item);
		GameItem* getItemByThisID(uint32 thisid);
		void removeItem(GameItem* item);
		void removeItem(uint32 thisid);

		bool addEntry(GameItem* item);
	private:

		typedef map<uint32,GameItem*> ItemMap;
		ItemMap m_item_manager;	
};

#endif
