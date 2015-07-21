#ifndef _ISE_PACKAGE_H_
#define _ISE_PACKAGE_H_


#include "ise/main/ise.h"


class PackageBase
{
	protected:
		PackageBase(GameItemManager* im, uint32 type);
		virtual ~PackageBase();
		
		void initCapacity();

	public:
		GameItem* getItemByThisID(uint32 thisid);
		GameItem* getItemByBaseID(uint32 baseid);
		GameItem* getItemByPosX(uint16 posX);

		virtual bool addItem(GameItem *item, AddItemAction act);

		virtual bool removeItem(GameItem *item, DelItemAction act, bool swap/* = false*/, uint32 &err);

		bool obtainItem(GameItem* &item, AddItemAction action);
	private:
		
		typedef map<uint32, GameItem*> PackItemMap;

		uint32 m_size;
		PackItemMap m_item_map; 
		const uint32 m_type;//背包类型
		uint16 m_upper_bound_grids;//格子上限
		
	public:
		GameItemManager* m_im;

};
class LuggablePackage:public PackageBase
{
	public:
		LuggablePackage(GameItemManager* im);
		~LuggablePackage();
};


class TreasurePackage:public PackageBase
{
	public:
		TreasurePackage(GameItemManager* im);
		~TreasurePackage();
};

class SoulPackage:public PackageBase
{
	public:
		SoulPackage(GameItemManager* im);
		~SoulPackage();
};

class EquipPackage 
{
	public:
		EquipPackage(GameItemManager* im,Entry *owner);
		~EquipPackage();

		inline GameItem* getClothes 	() const	{ return m_clothes		; }
		inline GameItem* getWeapon		() const	{ return m_weapon		; }
		inline GameItem* getGlove		() const	{ return m_glove		; }
		inline GameItem* getShoes		() const	{ return m_shoes		; }

	private:
		union
		{
			struct
			{
				GameItem *m_clothes		;  // 琛ｆ湇
				GameItem *m_weapon		;  // 姝﹀櫒
				GameItem *m_glove		;
				GameItem *m_shoes		;
			};
			GameItem *m_equips[EquipPosition_Max];
		}; 

		EquipSuitAttribute m_equipsuit_attrs;

};

class Hero
{

};
class SoulEquipPackage 
{
	public:
		SoulEquipPackage(GameEntry *entry);
		~SoulEquipPackage();
		GameItem *m_equips[MAX_SOUL_PACKAGE_SOLT];
		
};
class GamePlayerPackages
{

	GamePlayerPackages(GamePlayer *player);
	~GamePlayerPackages();

	bool obtainItem(GameItem* &item, AddItemAction action);

	
	private:

		LuggablePackage m_commom_pack;
		TreasurePackage m_treasure_pack;
		SoulPackage		m_soul_pack;


		SoulEquipPackage m_soul_equip_pack;
		EquipPackage	m_equip_pack;

		
		GameItemManager m_uim;
};


#endif
