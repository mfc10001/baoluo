
#include "BaseType.h"


enum EquipAttrGeneType
{
	EquipAttrGeneType_Base			= 0, 	///< 基础属性
	EquipAttrGeneType_Strengthen	= 1, 	///< 强化属性
	EquipAttrGeneType_Additional	= 2, 	///< 附加属性
	EquipAttrGeneType_Hidden		= 3, 	///< 隐藏属性
	EquipAttrGeneType_Hole1			= 4, 	///< 镶嵌属性孔1
	EquipAttrGeneType_Hole2			= 5, 	///< 镶嵌属性孔2
	EquipAttrGeneType_Hole3			= 6, 	///< 镶嵌属性孔3
	EquipAttrGeneType_Hole4			= 7, 	///< 镶嵌属性孔4
	EquipAttrGeneType_Reform		= 8, 	///< 洗炼
	EquipAttrGeneType_Ext		    = 9, 	///< 扩展属性

	EquipAttrGeneType_Max,
};




struct ItemBase
{
	union
	{
		struct
		{
			uint32 create_time;		///< 道具生成时间 
			uint32 first_thisid;	///< 第一次生成的thisid 
		};
		uint64 createid;
	};
	uint32 thisid;   			///< 道具唯一ID
	uint32 baseid;  			///< 道具表里的ID 
	uint32 num;					///< 道具数量

	ItemBase() {
		bzero(this, sizeof(ItemBase));
	}

	void init() {
		bzero(this, sizeof(ItemBase));
	}
};


struct ItemData : public ItemBase
{


	#define EQUIP_GET_ATTR_FUNC(name) \
		EquipAttrMap& get##name##Attr() \
		{ \
			EquipAttrMap*& p = equip_attr[EquipAttrGeneType_##name]; \
			if(p == NULL) p = new EquipAttrMap; \
			assert_log(p); \
			return *p; \
		}
		EQUIP_GET_ATTR_FUNC(Base		)	
		EQUIP_GET_ATTR_FUNC(Strengthen	)
		EQUIP_GET_ATTR_FUNC(Additional	)
		EQUIP_GET_ATTR_FUNC(Hidden		)
		EQUIP_GET_ATTR_FUNC(Hole1		)	
		EQUIP_GET_ATTR_FUNC(Hole2		)	
		EQUIP_GET_ATTR_FUNC(Hole3		)	
		EQUIP_GET_ATTR_FUNC(Hole4		)
		EQUIP_GET_ATTR_FUNC(Hole5		)
		EQUIP_GET_ATTR_FUNC(Hole6		)	
		EQUIP_GET_ATTR_FUNC(Reform		)	
		EQUIP_GET_ATTR_FUNC(Ext		    )	

	#undef EQUIP_GET_ATTR_FUNC

	EquipAttrMap* equip_attr[EquipAttrGeneType_Max]; ///< 装备属性
}

