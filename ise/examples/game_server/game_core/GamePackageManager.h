#ifndef _ISE_PACKAGEMANAGER_H_
#define _ISE_PACKAGEMANAGER_H_

#include "ise/main/ise.h"
#include "../game_define/ItemBase.h"
#include "../game_define/Protocol.h"
#include "GamePackage.h"
#include "ise/ext/utils/json/json.h"





class GamePlayerPackages
{
    public:
        GamePlayerPackages(GamePlayer *player);
        ~GamePlayerPackages();

        bool obtainItem(GameItem* &item, AddItemAction action);
		bool reduceItemNumByBaseID(const uint32 baseid, const uint32 num, DelItemAction action);

		bool deleteItem(GameItem* &item, DelItemAction action);


		void fill(Json::Value &data);

		
		uint32 onSolt(GameItem *item,uint8 pos);

		uint32 onSolt(uint32 thisid,uint8 pos);
		
		uint32 unfixSolt(uint32 pos);

		TreasureSolt &getTreasureSolt();

		
	public:

		LuggablePackage m_commom_pack;
		TreasurePackage m_treasure_pack;
		SoulPackage		m_soul_pack;
		SoulEquipPackage m_soul_equip_pack;
		EquipPackage	m_equip_pack;
		TreasureSolt    m_treasure_solt;
		
        friend class GameItemManager;
		GameItemManager m_uim;

		GamePlayer *m_owner;
};

#endif
