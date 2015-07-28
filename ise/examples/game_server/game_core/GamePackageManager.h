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
		bool reduceItemNumByThisID(uint32 thisid, uint32 num, DelItemAction action);

		void SendChangeItem(uint32 thisid,uint32 itemid,uint32 num,uint8 pack_type,bool opt);
		bool deleteItem(GameItem* &item, DelItemAction action);


		void fill(Json::Value &data);
		void fill(Json::Value &data,uint8 pos);
		void fillDBData(Json::Value &data);

		uint32 onSolt(GameItem *item,uint8 pos);

		uint32 onSolt(uint32 thisid,uint8 pos);

		uint32 unfixSolt(uint32 pos);

		TreasureSolt &getTreasureSolt();

		uint32 useItemByThisId(uint32 baseid,uint32 num=1);

		bool ReadJsonData(Json::Value &data);

	private:
		uint32 useItem(GameItem* item,uint32 num);
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
