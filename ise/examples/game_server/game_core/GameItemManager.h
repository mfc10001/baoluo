#ifndef _ISE_GAMEITEMMANAGER_H_
#define _ISE_GAMEITEMMANAGER_H_


#include "ise/main/ise.h"
#include "ConfigManager.h"
#include "../game_define/Protocol.h"
#include "../game_define/ItemBase.h"
class GameItem;
class GamePlayer;

class GameItemManager
{
    public:
        GameItemManager(GamePlayer *user);
        ~GameItemManager();

		//uint32 serialize(uint8* out, GamePlayer* player);
		//bool unSerialize(const SerializeDataMember* in, GamePlayer* owner);


		void save();
		void  fillDbData(Json::Value &arrayObj);

        GamePlayer *getOwner();

        bool addItem(GameItem* item);
        void removeItem(GameItem* item);

        friend class Singleton<GameItemManager>;

        ItemMap m_item_manager;
        GamePlayer *owner;

};

struct ItemCreator
{
    static GameItem* createItem(const ItemDataEntry *base, uint32 num, uint32 src_id, const char* src_name, const char *desc, AddItemAction action,  GamePlayer *owner = NULL);

	static bool autoUnionCreateItem(uint32 baseid, uint32 num, GamePlayer *owner, AddItemAction action);
	static void destroyItem(GameItem* &item, GamePlayer* owner, DelItemAction action);
};



class GlobalItemManager :public Singleton<GlobalItemManager>
{
	private:
		GlobalItemManager(){};
		~GlobalItemManager(){};

	public:
		bool addItem(GameItem* item);
		GameItem* getItemByThisID(uint32 thisid);
		void removeItem(GameItem* item);
		void removeItem(uint32 thisid);

		bool addEntry(GameItem* item);
	private:

		typedef map<uint32,GameItem*> ItemMap;
		ItemMap m_item_manager;

        friend class Singleton<GlobalItemManager>;
};

#endif
