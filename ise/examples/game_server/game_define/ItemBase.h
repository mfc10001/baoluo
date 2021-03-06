#ifndef _ISE_BASEITEM_H_
#define _ISE_BASEITEM_H_
#include "ise/main/ise.h"
#include "BaseType.h"


enum EquipAttrGeneType
{
	EquipAttrGeneType_Base			= 0, 	///< 基础属性
	EquipAttrGeneType_Strengthen	= 1, 	///< 强化属性
	EquipAttrGeneType_Hole1			= 2, 	///< 镶嵌属性孔1
	EquipAttrGeneType_Hole2			= 3, 	///< 镶嵌属性孔2
	EquipAttrGeneType_Hole3			= 4, 	///< 镶嵌属性孔3
	EquipAttrGeneType_Hole4			= 5, 	///< 镶嵌属性孔4

	EquipAttrGeneType_Max,
};



struct ItemBase
{
	uint32 thisid;   			///< 道具唯一ID
	uint32 baseid;  			///< 道具表里的ID
	uint32 num;					///< 道具数量
	uint8  base_type;
	uint32 create_time;
	uint8  pack_type;
	ItemBase() {
		bzero(this, sizeof(ItemBase));
	}

	void init() {
		bzero(this, sizeof(ItemBase));
	}
};


struct ItemData : public ItemBase
{
    ItemData()
    {
        memset(this,0,sizeof(ItemData));
    }
	#define EQUIP_GET_ATTR_FUNC(name) \
		uint32 get##name##Attr()\
		{\
			return equip_attr[EquipAttrGeneType_##name];\
		}

		EQUIP_GET_ATTR_FUNC(Base		)
		EQUIP_GET_ATTR_FUNC(Strengthen	)
		EQUIP_GET_ATTR_FUNC(Hole1		)
		EQUIP_GET_ATTR_FUNC(Hole2		)
		EQUIP_GET_ATTR_FUNC(Hole3		)
		EQUIP_GET_ATTR_FUNC(Hole4		)
	#undef EQUIP_GET_ATTR_FUNC

	void inc_strengthen(uint32 lev)
	{
		equip_attr[EquipAttrGeneType_Strengthen]+=lev;
	};


	uint32 equip_attr[EquipAttrGeneType_Max];


};



enum EquipPostion
{
	EquipPosition_Begin  				= 0,
	EquipPosition_Clothes				= 0,	// 衣服
	EquipPosition_Weapon				= 1,	// 武器
	EquipPosition_glove					= 2,
	EquipPosition_shoes					= 3,

	EquipPosition_Max,
};

enum TreasurePostion
{
	TreasurePostion_first				=0,
	TreasurePostion_second				=1,
	TreasurePostion_Max,
};


enum EquipSuitAttrType
{
	EquipSuitAttrType_None 				= 0,
	EquipSuitAttrType_AddHurt 			= 1,	//伤害提高			//数值 --
	EquipSuitAttrType_ResumeRagePerAction		= 2,	//每行动回复怒气		//数值
	EquipSuitAttrType_SubAngryCostByRatePer		= 3,	//一定机率使技能怒气消耗降低	//百分比
	EquipSuitAttrType_SubBeFatalAttackRatePer	= 4,	//受到暴击机率下降		//百分比
	EquipSuitAttrType_AddPhysique			= 5,	//增加体质			//数值
	EquipSuitAttrType_AddBattleStartRage		= 6,	//出场怒气下限增加		//数值
	EquipSuitAttrType_IgnoreTarDef			= 7,	//忽略对方防御			//数值
	EquipSuitAttrType_Max,
};



struct EquipSuitAttribute
{
	public:
		EquipSuitAttribute(){
			reset();
		}
		void reset(){
			bzero(this, sizeof(arr));
		}

		uint32 arr[EquipSuitAttrType_Max];

};

//��������
enum PackageType
{
	PackageType_Common=0,//��ͨ����
	PackageType_Soul,//Ԫ�����
	PackageType_Treasure,//�������
	PackageType_Equip,//װ������
	PackageType_Soul_Solt,
	PackageType_Treasure_solt,
	PackageType_Max,
};


enum PackageCap
{
	PackageCap_Equip		= EquipPosition_Max,			///< 装备包裹大小
	PackageCap_CommonInit		= 30,					///< 普通包裹初始大小
	PackageCap_CommonAdd		= 1, 					///< 一次购买添加的格子数量
	PackageCap_CommonMax		= 96, 					///< 普通包裹上限

	PackageCap_SoulInit		= 30,					///< 普通包裹初始大小
	PackageCap_SoulAdd		= 1, 					///< 一次购买添加的格子数量
	PackageCap_SoulMax		= 96, 					///< 普通包裹上限

	PackageCap_TreasureInit		= 30,					///< 普通包裹初始大小
	PackageCap_TreasureAdd		= 1, 					///< 一次购买添加的格子数量
	PackageCap_TreasureMax		= 96, 					///< 普通包裹上限


	PackageCap_Stor			= 80,					///< 仓库普通包裹初始大小

	PackageCap_SubalternEquip	= EquipPosition_Max - 1, 		///< 副官装备包裹的大小
	PackageCap_SubalternCommon	= 40,					///< 副官装备包裹的大小
};


enum DelItemAction
{
	DelItemAction_None		= 0,
	DelItemAction_CreateAddToPackageFail=1,
	DelItemAction_Improve	=2,

	DelItemAction_Max
};

enum AddItemAction
{
	AddItemAction_None			= 0,
	AddItemAction_MOVE			= 1,
	AddItemAction_Store         = 2,
	AddItemAction_Unseri		=3,

	AddItemAction_Max,
};

inline const char *getAddItemActionStr(uint8 act)
{
	static char *AddItemActionName[] =
	{
		"��",



	};
	return act < AddItemAction_Max ? AddItemActionName[act] : "异常的道具添加操作类型";
}


inline const char *getDelItemActionStr(uint8 act)
{
	static char *DelItemActionName[] =
	{
		"��",
	};
	return act < DelItemAction_Max ? DelItemActionName[act] : "异常的道具删除操作类型";
}


enum EquipAttrType
{
	EquipAttrType_None = 0,

	EquipAttrType_Max,
};

typedef std::map<EquipAttrType, uint32>		EquipAttrMap;


#endif
