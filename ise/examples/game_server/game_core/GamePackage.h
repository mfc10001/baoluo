

class GamePlayerPackages
{



	typedef ZQGame::vector<GameItem*> ItemVec;

	

	typedef ZQGame::map<uint32, GameItem*> PackItemMap;

	const uint32 m_type;//��������
	uint16 m_upper_bound_grids;//��������

	PackItemMap m_item_map;       
};

