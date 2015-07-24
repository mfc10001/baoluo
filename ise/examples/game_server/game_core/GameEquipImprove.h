
#ifndef _ISE_IMPROVE_H_
#define _ISE_IMPROVE_H_


#include "ise/main/ise.h"

class GamePlayer;
class GameItem;

class EquipImprove
{
	public:
		EquipImprove(GamePlayer *player);
		~EquipImprove();

		uint32 strengthenEquip(uint32 thisid);

		uint32 cost(GameItem* item);

	private:
		//@brief	属主
		GamePlayer* m_owner;

};

#endif
