
#include "GamePackageManager.h"
#include "GameItem.h"
GamePlayerPackages::GamePlayerPackages(GamePlayer *player)
: m_uim(player),
m_commom_pack(&m_uim),
m_treasure_pack(&m_uim),
m_soul_pack(&m_uim),
m_equip_pack(player),
m_soul_equip_pack(&m_uim),
m_treasure_solt(player),
m_owner(player)
{

}
GamePlayerPackages::~GamePlayerPackages()
{

}
void GamePlayerPackages::SendChangeItem(uint32 thisid,uint32 num,uint8 pack_type,bool opt)
{
	uint32 err=ERR_SUCCESS;
	Json::Value rValue;
	Json::Value rData;
	uint32 rNo=PROTOCOL_ITEM_NOTITY_S;

	rData["thisid"]=thisid;
	rData["changnum"]=num;
	rData["pack_type"]=pack_type;
	rData["opt"]=opt;

	rValue["code"]=err;
	rValue["type"]=rNo;
	rValue["data"]=rData;
	string str = rValue.toStyledString();

	char buff[MAX_SEND_BUFF];
	memset(buff,0,MAX_SEND_BUFF);
	uint16 len=str.length()+2;
	memcpy(buff,&len,sizeof(uint16));
	memcpy(buff+2,str.c_str(),str.length());
	LinuxTcpConnection*  pp =  static_cast<LinuxTcpConnection*> (&m_owner->getCon());
	pp->send(buff,len);
}

bool GamePlayerPackages::obtainItem(GameItem* &item, AddItemAction action)
{
	if(item)
	{
		switch(item->getBaseType())
		{
			case PackageType_Common:
				{
					 m_commom_pack.addItem(item,action);
				}
				break;
			case PackageType_Soul:
				{
					 m_soul_pack.addItem(item,action);
				}
				break;
			case PackageType_Treasure:
				{
					 m_treasure_pack.addItem(item,action);
				}
				break;
			default:
				return false;
		}
	}
	else
		{
		return false;
	}
	SendChangeItem(item->getEntryID(),item->m_data.num,item->getPackType(),true);
	return true;
}

bool GamePlayerPackages::deleteItem(GameItem* &item, DelItemAction action)
{
	CheckCondition(item && m_owner, false);
    uint32 ret=0;
	if(m_commom_pack.removeItem(item,action,ret))
    {
        ItemCreator::destroyItem(item, m_owner, action);
    }

}
bool GamePlayerPackages::reduceItemNumByThisID(uint32 thisid, uint32 num, DelItemAction action)
{
	GameItem *item = m_uim.getItemByThisID(thisid);
	CheckCondition(item, false);

	if(item->m_data.num < num)
	{
		return false;
	}

	if(item->m_data.num == num)
	{
		return deleteItem(item, action);
	}

	
	SendChangeItem(thisid,num,item->getPackType(),false);
	return item->subNumber(num, m_owner, action);
}

bool GamePlayerPackages::reduceItemNumByBaseID(uint32 baseid, uint32 num, DelItemAction action)
{
	return false;
	vector<GameItem*>  dellist;
	GameItem* last_del;
	bool ret=false;
	for(ItemMap::iterator it = m_uim.m_item_manager.begin();it !=m_uim.m_item_manager.end();it++)
	{
		GameItem *entry=(*it).second;
		if(entry->getBaseID()==baseid)
		{
			if(num >= entry->m_data.num)
			{
				dellist.push_back(entry);
				num=num-entry->m_data.num;
				if(num == 0)
				{
					ret= true;
				}
			}
			else
			{
				last_del = entry;
				ret= true;
			}
		}
	}

	vector<GameItem*>::iterator iter = dellist.begin(), end = dellist.end();
	for(; iter != end; ++ iter)
	{
		deleteItem(*iter, action);
	}


	if(last_del)
	{
		last_del->subNumber(num, m_owner, action);
	}
	if(ret)
	{
			
	}
	return ret;
}



uint32 GamePlayerPackages::unfixSolt(uint32 pos)
{
	CheckCondition(pos<TreasurePostion_Max,ERR_INNER);
	GameItem * item = m_treasure_solt.m_treausre[pos];
	CheckCondition(item,ERR_INNER);

	CheckCondition (m_commom_pack.checkLeftSpace(),ERR_VALID_GRIDS);

	if(m_commom_pack.moveItemIn(item))
	{
		m_treasure_solt.m_treausre[pos]=NULL;
		return ERR_SUCCESS;
	}
	return ERR_INNER;
}
uint32 GamePlayerPackages::onSolt(GameItem *item,uint8 pos)
{
	uint32 ret = m_treasure_solt.onEquip(item,pos);
	if(ret ==ERR_SUCCESS)
	{
		m_commom_pack.moveItOut(item);
	}
}

uint32 GamePlayerPackages::onSolt(uint32 thisid,uint8 pos)
{
	GameItem *item = m_uim.getItemByThisID(thisid);
	CheckCondition(thisid,ERR_PARAMS);

	CheckCondition(item->m_data.pack_type!=pos,ERR_PACK_POS_EXIST);

	return ERR_SUCCESS;
}

void GamePlayerPackages::fillDBData(Json::Value &data)
{
	m_equip_pack.fillData(data["equip"]);
	m_uim.fillDbData(data["uin"]);
}

void GamePlayerPackages::fill(Json::Value &data)
{
	m_uim.fillDbData(data);
}
void GamePlayerPackages::fill(Json::Value &data,uint8 pos)
{
    if(pos==PackageType_Equip)
    {
        m_equip_pack.fillData(data);
    }
    else
    {
        m_uim.fillDbData(data,pos);
    }
}
uint32 GamePlayerPackages::useItemByThisId(uint32 thisid,uint32 num)
{
	GameItem *item = m_uim.getItemByThisID(thisid);
	CheckCondition(item, ERR_ITEM_NOTEXIST);

	return useItem(item,num);
}
uint32 GamePlayerPackages::useItem(GameItem* item,uint32 num)
{
	return 0;
}


