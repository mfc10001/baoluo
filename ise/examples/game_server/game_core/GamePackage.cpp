#include "GamePackage.h"




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
GameItem* PackageBase::getItemByThisID(uint32 thisid)
{
	PackItemMap::iterator it = m_item_map.find(thisid);
	if(it==m_item_map.edn())
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

bool PackageBase::addItem(GameItem *item, AddItemAction act)
{
	if (!item){
        return false;
    }

	GameItem* self_item = getItemByBaseID(item->getBaseID())
	if(self_item)
	{
		if(self_item->m_base_data->add_max==0)
		{
			 self_item->incNumber(item->getItemNumber());
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

bool GamePlayerPackages::obtainItem(GameItem* &item, AddItemAction action)
{
	if(item)
	{
		switch(item->getBaseType())
		{
			case PackageType_Common:
				{
					return m_commom_pack.addItem(item,action);
				}
				break;
			case PackageType_Soul:
				{
					return m_soul_pack.addItem(item,action);
				}
				break;
			case PackageType_Treasure:
				{
					return m_treasure_pack.addItem(item,action);
				}
				break;
			case PackageType_Equip:
				{
					
				}
				break;
			default:
				return false;
		}
	}
	return true;
}



GamePlayerPackages::GamePlayerPackages(GamePlayer *player)
: m_equip_pack(player, &m_uim)
{
	
}
GamePlayerPackages::~GamePlayerPackages()
{
	
}


EquipPackage::EquipPackage(GameItemManager* im)
{
	
}
EquipPackage::~EquipPackage()
{
	
}

