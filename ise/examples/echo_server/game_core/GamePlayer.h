#ifndef _ISE_PLAYER_H_
#define _ISE_PLAYER_H_

#include "../bass_class/Entry.h"

enum PlayerAttr
{	
	PlayerAttr_Max=48;
};


class GamePlayer
{
	public:
		GamePlayer();
		~GamePlayer();
	
	private:
		uint32 m_base_data[PlayerAttr_Max];
};


#endif
