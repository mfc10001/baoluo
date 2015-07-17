

class GameItemManager :public Singleton<ConfigManager>
{


    friend class Singleton<GameItemManager>;

};


class GameEquipManager :public Singleton<ConfigManager>
{
	
    friend class Singleton<GameEquipManager>;
};

