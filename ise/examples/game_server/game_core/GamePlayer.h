#ifndef _ISE_PLAYER_H_
#define _ISE_PLAYER_H_

#include "../bass_class/Entry.h"
#include "ise/main/ise.h"
#include "../game_define/Protocol.h"
#include "ise/ext/utils/json/json.h"


#define MAX_NAME_SIZE 50
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



	PlayerAttr_Max=48
};

struct PlayerBaseAttr
{
	char name[MAX_NAME_SIZE];
	uint32 role;
	uint8 init_flag;

	uint16 level;
	uint32 exp;

};

typedef boost::function<void ()> PlayerLevelHandlerCallback;


class GamePlayer
{
	public:
		GamePlayer();
		~GamePlayer();
		void createChar();

		void setBaseAttr(uint16 type,uint32 value);

		void addExp(uint32 num);
		void levelUp();


		void setRole(uint8 type);

		void save();

		void registerPlayerHandler(const PlayerLevelHandlerCallback& callback);

		void init(Json::Value &data);

		uint32 getUid();

		void  fillClientData(Json::Value &arrayObj);
		void  fillDbData(Json::Value &arrayObj);
	private:
		uint32 uid;


		PlayerBaseAttr m_base_attr;
		uint32 m_base_data[PlayerAttr_Max];


};


#endif
