#ifndef _ISE_PLAYER_H_
#define _ISE_PLAYER_H_

#include "../bass_class/Entry.h"
#include "ise/main/ise.h"
#include "../game_define/Protocol.h"
#include "ise/ext/utils/json/json.h"
#include "GamePackage.h"
#include "../game_define/EntryBase.h"



class GamePlayer:GameEntry
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


		
		uint32 m_base_data[PlayerAttr_Max];

		GamePlayerPackages m_pack_manager;


};


#endif
