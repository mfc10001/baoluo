#include ""
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



	PlayerAttr_Max=48,
};

struct PlayerBaseAttr
{
    PlayerBaseAttr()
    {
        memset(this,0,sizeof(*this));
    }
	char name[MAX_NAME_SIZE];
	uint32 role;
	uint8 init_flag;

	uint16 level;
	uint32 exp;

};

typedef boost::function<void ()> PlayerLevelHandlerCallback;

