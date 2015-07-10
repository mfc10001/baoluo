#ifndef _ISE_PLAYER_H_
#define _ISE_PLAYER_H_

#include "../bass_class/Entry.h"


#define MAX_NAME_SIZE 50;
enum PlayerAttr
{	
	PlayerAttr_physicsAttack=0,
	PlayerAttr_magicAttack,
	PlayerAttr_barmor,
	PlayerAttr_bresistance,
	PlayerAttr_hp,
	PlayerAttr_hit,
	PlayerAttr_dodge,
	PlayerAttr_crit,
	PlayerAttr_opposeCrit,
	PlayerAttr_physicsAttackz,
	PlayerAttr_magicAttackz,
	PlayerAttr_barmorz,
	PlayerAttr_bresistancez,
	PlayerAttr_hpz,
	PlayerAttr_hitz,
	PlayerAttr_dodgez,
	PlayerAttr_critz,
	PlayerAttr_opposeCritz,



	PlayerAttr_Max=48;
};


class GamePlayer
{
	public:
		GamePlayer();
		~GamePlayer();
		void createChar(uint32 id);

		void setBaseAttr(uint16 type,uint32 value);
	
	private:
		uint32 m_base_data[PlayerAttr_Max];
};


#endif
