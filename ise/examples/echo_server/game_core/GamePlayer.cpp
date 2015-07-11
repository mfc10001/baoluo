#include "GamePlayer.h"
#include "ConfigManager.h"


GamePlayer::GamePlayer()
{

}
GamePlayer::~GamePlayer()
{

}


void GamePlayer::createChar(uint32 id)
{
	const ConfigPlayerData *ptr_data=ConfigManager::instance().getPlayerData(id);
	if(!ptr_data)
	{
		return;
	}

	setBaseAttr(PlayerAttr_physicsAttack,ptr_data->physicsAttack  );
	setBaseAttr(PlayerAttr_magicAttack,ptr_data->magicAttack  );
	setBaseAttr(PlayerAttr_barmor,ptr_data->barmor  );
	setBaseAttr(PlayerAttr_bresistance,ptr_data->bresistance  );
	setBaseAttr(PlayerAttr_hp,ptr_data->hp  );
	setBaseAttr(PlayerAttr_hit,ptr_data->hit);
	setBaseAttr(PlayerAttr_dodge,ptr_data->dodge);
	setBaseAttr(PlayerAttr_crit,ptr_data->crit);
	setBaseAttr(PlayerAttr_opposeCrit,ptr_data->opposeCrit);

	/*
	setBaseAttr(PlayerAttr_physicsAttackz,ptr_data->  )
	setBaseAttr(PlayerAttr_magicAttackz,ptr_data->  )
	setBaseAttr(PlayerAttr_barmorz,ptr_data->  )
	setBaseAttr(PlayerAttr_bresistancez,ptr_data->  )
	setBaseAttr(PlayerAttr_hpz,ptr_data->  )
	setBaseAttr(PlayerAttr_hitz,ptr_data->  )
	setBaseAttr(PlayerAttr_dodgez,ptr_data->  )
	setBaseAttr(PlayerAttr_critz,ptr_data->  )
	setBaseAttr(PlayerAttr_opposeCritz,ptr_data->  )
*/


}
void GamePlayer::setBaseAttr(uint16 type,uint32 value)
{
	if(type>PlayerAttr_Max)
	{
		return;
	}
	m_base_data[type]=value;
}


