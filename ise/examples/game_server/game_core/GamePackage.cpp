
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
	if (!item){
        return false;
    }

	GameItem* self_item = getItemByBaseID(item->getBaseID());
	if(self_item)
	{
		if(self_item->m_base_data->add_max==0)
		{
			 self_item->incNumber(item->getItemNumber(),getOwner(),act);
			 return false;
		}
	}

	if(m_im->addItem(item))
	{
		m_item_map.insert(std::make_pair(item->id, item));
		++m_size;
		return true;
	}
	return false;
}

bool PackageBase::removeItem(GameItem* item, DelItemAction act, bool swap, uint32 &err)
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
EquipPackage::EquipPackage(GameItemManager* im)
:PackageBase(im, PackageType_Equip)
{

}
EquipPackage::~EquipPackage()
{

}

SoulEquipPackage::SoulEquipPackage(GameItemManager* im)
:PackageBase(im, PackageType_Soul_Solt)
{

}
SoulEquipPackage::~SoulEquipPackage()
{

}
