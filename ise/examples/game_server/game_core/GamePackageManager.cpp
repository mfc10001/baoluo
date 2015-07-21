
#include "GamePackageManager.h"
#include "GameItem.h"
GamePlayerPackages::GamePlayerPackages(GamePlayer *player)
: m_uim(player),
m_commom_pack(&m_uim),
m_treasure_pack(&m_uim),
m_soul_pack(&m_uim),
m_equip_pack(&m_uim),
m_soul_equip_pack(&m_uim)
{

}
GamePlayerPackages::~GamePlayerPackages()
{

}

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

