#ifndef _ISE_GAMEITEM_H_
#define _ISE_GAMEITEM_H_


#include "ise/main/ise.h"
#include "../game_define/ItemBase.h"

class GameItem:public Entry
{
	void generateThisID();
	uint8 getBaseType();
	uint32 getBaseID();
	uint32 getItemNumber();
	
	bool incNumber(uint32 num, GamePlayer *player, AddItemAction act);
	bool subNumber(uint32 num, GamePlayer *player, DelItemAction act);
	
	ItemData m_data;
	const ItemDataEntry *m_base_data;
}

#endif