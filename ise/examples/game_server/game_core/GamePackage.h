

class GamePlayerPackages
{



	typedef ZQGame::vector<GameItem*> ItemVec;

	

	typedef ZQGame::map<uint32, GameItem*> PackItemMap;

	const uint32 m_type;//背包类型
	uint16 m_upper_bound_grids;//格子上限

	PackItemMap m_item_map;       
};

