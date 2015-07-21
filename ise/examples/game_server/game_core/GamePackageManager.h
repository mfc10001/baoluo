#ifndef _ISE_PACKAGEMANAGER_H_
#define _ISE_PACKAGEMANAGER_H_

#include "ise/main/ise.h"
#include "../game_define/ItemBase.h"
#include "../game_define/Protocol.h"
#include "GamePackage.h"





class GamePlayerPackages
{
    public:
        GamePlayerPackages(GamePlayer *player);
        ~GamePlayerPackages();

        bool obtainItem(GameItem* &item, AddItemAction action);


	private:

		LuggablePackage m_commom_pack;
		TreasurePackage m_treasure_pack;
		SoulPackage		m_soul_pack;


		SoulEquipPackage m_soul_equip_pack;
		EquipPackage	m_equip_pack;

        friend class GameItemManager;
		GameItemManager m_uim;
};

#endif
