#ifndef _ISE_PLAYER_H_
#define _ISE_PLAYER_H_

#include "../bass_class/Entry.h"
#include "ise/main/ise.h"
#include "../game_define/Protocol.h"
#include "ise/ext/utils/json/json.h"
#include "../game_define/EntryBase.h"
#include "GamePackageManager.h"
#include "Game"

class GamePlayer:public GameEntry
{
	public:
		GamePlayer();
		~GamePlayer();
		void createChar();

		void setBaseAttr(uint16 type,uint32 value);

		void addExp(uint32 num);
		void levelUp();

        uint32 getRole(){return m_base_attr.role;};
		void setRole(uint8 type);

		void save();

		void registerPlayerHandler(const PlayerLevelHandlerCallback& callback);

		void init(Json::Value &data);

		uint32 getUid();

		void  fillClientData(Json::Value &arrayObj);
		void  fillDbData(Json::Value &arrayObj);


		bool checkMoney(MoneyType eType, const uint64 num);
		uint64 	getMoney(MoneyType eType) const;
		void 	addMoney(MoneyType eType, const uint64 num, AddMoneyAction action, bool notify = true);
		bool 	subMoney(MoneyType eType, const uint64 num, DelMoneyAction action, bool notify = true);
	private:

		void addMoney(MoneyType eType, const uint64 money);
		void subMoney(MoneyType eType, const uint64 money);
	public:
        GamePlayerPackages m_pack_manager;
		EquipImprove       m_improve;

	private:
		uint32 uid;
		uint32 m_base_data[PlayerAttr_Max];

		uint32 m_packet[MoneyType_End];

};


#endif
