
#include "GameItemManager.h"
#include "../game_define/EntryBase.h"
#include "GamePlayer.h"
#include "../bass_class/Entry.h"
#include "../game_define/ItemBase.h"
#include "GameItem.h"
PackageBase::PackageBase(GameItemManager* im, uint32 type)
	: m_size(0)
	, m_type(type)
	, m_im(im)

{
	initCapacity();
}

inline uint32 PackageBase::getValidCapacity()
{
	return m_valid_grids;
}

bool PackageBase::checkLeftSpace()
{
	return getValidCapacity() > m_size;
}


void PackageBase::initCapacity()
{
	switch(m_type)
	{
		case PackageType_Equip:
			{
				m_valid_grids		= PackageCap_Equip;
				m_upper_bound_grids 	= PackageCap_Equip;
			}
			break;

		case PackageType_Common:
			{
				m_valid_grids		= PackageCap_CommonInit;
				m_upper_bound_grids 	= PackageCap_CommonMax;
			}
			break;
		case PackageType_Soul:
			{
				m_valid_grids		= PackageCap_SoulInit;
				m_upper_bound_grids 	= PackageCap_SoulMax;
			}
			break;

		case PackageType_Treasure:
			{
				m_valid_grids		= PackageCap_TreasureInit;
				m_upper_bound_grids 	= PackageCap_TreasureMax;
			}
			break;

		default:
			break;
    }
}
GameItem* PackageBase::getItemByThisID(uint32 thisid)
{
	PackItemMap::iterator it = m_item_map.find(thisid);
	if(it==m_item_map.end())
	{
		return NULL;
	}
	return (*it).second;
}
GameItem* PackageBase::getItemByBaseID(uint32 baseid)
{
	return NULL;
}
GameItem* PackageBase::getItemByPosX(uint16 posX)
{
	return NULL;

}
GamePlayer * PackageBase::getOwner()
{
    m_im->getOwner();
}
bool PackageBase::addItem(GameItem *item, AddItemAction act)
{
	CheckCondition(item,false);
	CheckCondition(getValidCapacity(),false);

	GameItem* self_item = getItemByBaseID(item->getBaseID());
	if(self_item)
	{
        self_item->incNumber(item->getItemNumber(),getOwner(),act);
	}

	if(m_im->addItem(item))
	{
		m_item_map.insert(std::make_pair(item->id, item));
		++m_size;
		return true;
	}
	return false;
}

bool PackageBase::removeItem(GameItem* item, DelItemAction act,  uint32 &err)
{
    if (!item){
        err = ERR_INNER;
        return false;
    }

	m_im->removeItem(item);
	m_item_map.erase(item->id);
	--m_size;
	return true;
}
bool PackageBase::moveItemIn(GameItem *item)
{
	CheckCondition(getValidCapacity(),false);
	m_item_map.insert(std::make_pair(item->id, item));
	++m_size;
	return true;
}


/////
LuggablePackage::LuggablePackage(GameItemManager* im)
:PackageBase(im, PackageType_Common)
{

}
LuggablePackage::~LuggablePackage()
{

}

////
TreasurePackage::TreasurePackage(GameItemManager* im)
:PackageBase(im, PackageType_Treasure)
{

}

TreasurePackage::~TreasurePackage()
{

}



///
SoulPackage::SoulPackage(GameItemManager* im)
:PackageBase(im, PackageType_Soul)
{

}
SoulPackage::~SoulPackage()
{
}





//
EquipPackage::EquipPackage(GamePlayer *user):
m_owner(user)
{

}
EquipPackage::~EquipPackage()
{

}
void EquipPackage::fillData(Json::Value  &data)
{
    for(uint8 i = EquipPosition_Begin;i<EquipPosition_Max;i++)
    {
        Json::Value  temp;
        temp["pos"]=i;
        temp["level"]=m_equip_pos;
    }
}

uint32  EquipPackage::cost(uint32 level)
{
	uint32 coststonenum=0;
	uint32 costmoney=100;

	uint32 money = m_owner->getMoney(MoneyType_Money);

	if(coststonenum != 0)
	{
		GameItem *stone = m_owner->m_pack_manager.m_commom_pack.getItemByBaseID(100001);
		CheckCondition(stone,ERR_STONE);
		CheckCondition(stone->getItemNumber()>coststonenum,ERR_STONE);
	}

	CheckCondition(money>=costmoney,ERR_MONEY);


	m_owner->subMoney(MoneyType_Money,costmoney,DelMoneyAction_EquipImprove);
	if(coststonenum != 0)
	{
		m_owner->m_pack_manager.reduceItemNumByBaseID(100001,coststonenum,DelItemAction_Improve);
	}
	return ERR_SUCCESS;
}

uint32 EquipPackage::Improve(uint8 type)
{
	uint32 ret = cost(m_equip_pos[type].getLevel());
	if(ret == ERR_SUCCESS)
	{
		m_equip_pos[type].levelUp();
	}
	return ret;
}




/*
GameItem * EquipPackage::getEquip(uint8 pos)
{
	switch(pos)
	{
		case EquipPosition_Clothes:
			return getClothes();
		case EquipPosition_Weapon:
			return getWeapon();
		case EquipPosition_glove:
			return getGlove();
		case EquipPosition_shoes:
			return getShoes();
		default:
			return NULL;
	}
}
*/


////
SoulEquipPackage::SoulEquipPackage(GameItemManager* im)
:PackageBase(im, PackageType_Soul_Solt)
{

}
SoulEquipPackage::~SoulEquipPackage()
{

}


//
TreasureSolt::TreasureSolt(GamePlayer *user):
m_owner(user)
{

}
TreasureSolt::~TreasureSolt()
{

}

bool TreasureSolt::checkPosValid(uint8 type)
{
	CheckCondition(type<TreasurePostion_Max,false);
	GameItem * item = m_treausre[type];
	if(item)
	{
		return false;
	}
	return true;
}
uint32  TreasureSolt::onEquip(GameItem *item,uint8 pos)
{
	CheckCondition(item,ERR_INNER);
	CheckCondition(checkPosValid(pos),ERR_POSITION);
	m_treausre[pos]=item;
}


