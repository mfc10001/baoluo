#ifndef _ISE_PACKAGE_H_
#define _ISE_PACKAGE_H_


#include "ise/main/ise.h"
#include "../game_define/ItemBase.h"
#include "GameItemManager.h"
#include "../game_define/Protocol.h"
class GameItem;
class GameEntry;
class GamePlayer;
class Entry;
class GameItemManager;

class PackageBase
{
	protected:
		PackageBase(GameItemManager* im, uint32 type);
		virtual ~PackageBase(){};

		void initCapacity();

	public:
		GameItem* getItemByThisID(uint32 thisid);
		GameItem* getItemByBaseID(uint32 baseid);
		GameItem* getItemByPosX(uint16 posX);

		virtual bool addItem(GameItem *item, AddItemAction act);

		bool moveItemIn(GameItem *item);

		virtual bool removeItem(GameItem *item, DelItemAction act, uint32 &err);

		bool obtainItem(GameItem* &item, AddItemAction action);

		inline uint32 getValidCapacity() ;
		bool checkLeftSpace();

		GamePlayer * getOwner();
	private:

		typedef map<uint32, GameItem*> PackItemMap;

		uint32 m_size;
		PackItemMap m_item_map;
		const uint32 m_type;//背包类型
		uint16 m_upper_bound_grids;//格子上限
		uint32 m_valid_grids;

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


struct EquipBaseData
{
	uint32 trid;
	uint32 level;
	void levelUp(uint32 lev=1)
	{
		CheckConditionVoid(level+lev<=60);
		level+=lev;
	};

	uint32 getLevel()
	{
		return level;
	}
};
class EquipPackage
{
	public:
		EquipPackage(GamePlayer *user);
		~EquipPackage();
/*
		inline GameItem* getClothes 	() const	{ return m_clothes		; }
		inline GameItem* getWeapon		() const	{ return m_weapon		; }
		inline GameItem* getGlove		() const	{ return m_glove		; }
		inline GameItem* getShoes		() const	{ return m_shoes		; }

		GameItem * getEquip(uint8 pos);
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
*/

	uint32 Improve(uint8 type);
	uint32 cost(uint32 level);

	EquipBaseData m_equip_pos[EquipPosition_Max];

	GamePlayer *m_owner;

};


class SoulEquipPackage:public PackageBase
{
	public:
		SoulEquipPackage(GameItemManager* im);
		~SoulEquipPackage();
		GameItem *m_equips[MAX_SOUL_PACKAGE_SOLT];

};


class TreasureSolt
{
    public:
	TreasureSolt(GamePlayer *user);
	~TreasureSolt();
	bool checkPosValid(uint8 type);
	uint32  onEquip(GameItem *item,uint8 pos);
	uint32  moveEquipOut(uint8 pos);

	inline GameItem* getTreasure1 		() const	{ return m_treausre[TreasurePostion_first]		; }
	inline GameItem* getTreasure2		() const	{ return m_treausre[TreasurePostion_second]		; }

	GameItem *m_treausre[TreasurePostion_Max];

	GamePlayer *m_owner;
};


class Hero
{

};

#endif
