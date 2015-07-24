#include "GamePlayer.h"
#include "ConfigManager.h"
#include "../tools/CommonTools.h"
#include "../main_server.h"

GamePlayer::GamePlayer(TcpConnection &con)
:m_pack_manager(this),
m_improve(this),
connection(con)
{
}
GamePlayer::~GamePlayer()
{

}

void GamePlayer::setRole(uint8 type)
{
	m_base_attr.role=type;
}


void GamePlayer::createChar()
{
	const PlayerDataEntry *ptr_data=ConfigManager::instance().getPlayerData(m_base_attr.role);
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


	m_base_attr.init_flag=1;


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

void GamePlayer::save()
{
	Json::Value data;
	data["type"]= INNER_SAVE_PLAYER_BASE_DATA;
	fillDbData(data["data"]["base"]);
	m_pack_manager.m_uim.fillDbData(data["data"]["package"]);

	AppBusiness::sendToDb(data);

	/*
	MySqlQuery *query=static_cast<MySqlQuery *> (m_db_conn->createDbQuery());

	char buff[BUFFLEN];
	memset(buff,0,BUFFLEN);
	sprintf(buff,"update bl_user set level=%s , exp=%s  where uid=%s",m_base_attr.level,m_base_attr.exp,this->uid);
    query->setSql(buff);
	try
	{
		query->execute();
	}
   	catch(Exception)
   	{
		//»’÷æ
   	}
   	*/


}
void GamePlayer::addExp(uint32 num)
{

}
void GamePlayer::levelUp()
{

}
uint32 GamePlayer::getUid()
{
    return uid;
}
void GamePlayer::registerPlayerHandler(const PlayerLevelHandlerCallback& callback)
{
	//Functor level=boost::bind(levelUp);
}
void GamePlayer::init(Json::Value &arrayObj)
{
	uid = arrayObj["uid"].asUInt();
	string namestr = arrayObj["name"].asString();
	memcpy(m_base_attr.name,namestr.c_str(),namestr.length());

	m_base_attr.role = arrayObj["role"].asUInt();
	m_base_attr.level = arrayObj["level"].asUInt();
	m_base_attr.exp = arrayObj["exp"].asUInt();

	if(arrayObj["initFlag"]==0)
	{
		createChar();
		return;
	}


	m_base_data[ PlayerAttr_physicsAttack] = arrayObj["physicsAttack"].asUInt();
	m_base_data[ PlayerAttr_magicAttack]	= arrayObj["magicAttack"].asUInt();
	m_base_data[ PlayerAttr_barmor	]	= arrayObj["barmor"].asUInt();
	m_base_data[ PlayerAttr_bresistance]	= arrayObj["bresistance"].asUInt();
	m_base_data[ PlayerAttr_hp	]	= arrayObj["hp"].asUInt();
	m_base_data[ PlayerAttr_hit	]	= arrayObj["hit"].asUInt();
	m_base_data[ PlayerAttr_dodge	]	= arrayObj["dodge"].asUInt();
	m_base_data[ PlayerAttr_crit	]	= arrayObj["crit"].asUInt();


}

void  GamePlayer::fillClientData(Json::Value &arrayObj)
{
	arrayObj["uid"]=uid;
	arrayObj["name"]=m_base_attr.name;
	arrayObj["role"]=m_base_attr.role;
	arrayObj["level"]=m_base_attr.level;
	arrayObj["exp"]=m_base_attr.exp;

	arrayObj["physicsAttack"] =m_base_data[ PlayerAttr_physicsAttack];
	arrayObj["magicAttack"]=   m_base_data[ PlayerAttr_magicAttack];
	arrayObj["barmor"]= 	   m_base_data[ PlayerAttr_barmor  ];
	arrayObj["bresistance"]=   m_base_data[ PlayerAttr_bresistance];
	arrayObj["hp"]= 		   m_base_data[ PlayerAttr_hp  ];
	arrayObj["hit"]=		   m_base_data[ PlayerAttr_hit ];
	arrayObj["dodge"]=		   m_base_data[ PlayerAttr_dodge   ];
	arrayObj["crit"]=		   m_base_data[ PlayerAttr_crit    ];
}


void  GamePlayer::fillDbData(Json::Value &arrayObj)
{
	arrayObj["uid"]=uid;
	arrayObj["exp"]=m_base_attr.exp;
	arrayObj["init_flag"]=m_base_attr.init_flag;


	arrayObj["physicsAttack"] =m_base_data[ PlayerAttr_physicsAttack];
	arrayObj["magicAttack"]=   m_base_data[ PlayerAttr_magicAttack];
	arrayObj["barmor"]= 	   m_base_data[ PlayerAttr_barmor  ];
	arrayObj["bresistance"]=   m_base_data[ PlayerAttr_bresistance];
	arrayObj["hp"]= 		   m_base_data[ PlayerAttr_hp  ];
	arrayObj["hit"]=		   m_base_data[ PlayerAttr_hit ];
	arrayObj["dodge"]=		   m_base_data[ PlayerAttr_dodge   ];
	arrayObj["crit"]=		   m_base_data[ PlayerAttr_crit    ];
}

bool GamePlayer::checkMoney(MoneyType eType, const uint64 num)
{
	CheckCondition(isMoneyTypeValid(eType) && num <= MONEY_LIMIT, false);
	return m_packet[eType] >= num;
}

void GamePlayer::sendMoneyToMe(MoneyType eType, int change)
{
	uint32 err=ERR_SUCCESS;
	Json::Value rValue;
	Json::Value rData;

	uint32 rNo=PROTOCOL_CHAR_MONEY_S;

	rData["money_type"]=eType;
	rData["change"]=change;
	rData["total"]=m_packet[eType];

	SEND_DATA_TO_CLIENT

}

void GamePlayer::addMoney(MoneyType eType, const uint64 num, AddMoneyAction action, bool notify)
{
	CheckConditionVoid(isMoneyTypeValid(eType) && num <= MONEY_LIMIT && num > 0);
	addMoney(eType, num);

	if(notify)
	{
		sendMoneyToMe(eType, num);
	}
}
bool GamePlayer::subMoney(MoneyType eType, const uint64 num, DelMoneyAction action, bool notify)
{
	CheckCondition(num && checkMoney(eType, num), false);
	subMoney(eType, num);
	if(notify)
	{
		sendMoneyToMe(eType, num);
	}
	return true;
}



void GamePlayer::addMoney(MoneyType eType, const uint64 money)
{
	CheckConditionVoid(isMoneyTypeValid(eType) && money <= MONEY_LIMIT);
	uint64 n64Tmp = m_packet[eType] + money;
	n64Tmp = std::min(MONEY_LIMIT, n64Tmp) ;
	m_packet[eType] = n64Tmp;
}

void GamePlayer::subMoney(MoneyType eType, const uint64 money)
{
	CheckConditionVoid(isMoneyTypeValid(eType) && money <= MONEY_LIMIT);
	m_packet[eType] = m_packet[eType] > money ? m_packet[eType] - money : 0;
}

uint64 GamePlayer::getMoney(MoneyType eType) const
{
	CheckCondition(isMoneyTypeValid(eType), 0);
	return m_packet[eType];
}


