#ifndef _ISE_GAMEITEM_H_
#define _ISE_GAMEITEM_H_


#include "ise/main/ise.h"
#include "../game_define/ItemBase.h"
#include "GamePlayer.h"
#include "../game_define/EntryBase.h"

class GamePlayer;
class GameItem:public Entry
{
    public:
        void generateThisID();
        uint8 getBaseType();
        uint32 getBaseID();
        uint32 getItemNumber();
        bool incNumber(uint32 num, GamePlayer *player, AddItemAction act);
        bool subNumber(uint32 num, GamePlayer *player, DelItemAction act);
        void updateEquipStrengthenLev();
        ItemData m_data;
};

#endif
