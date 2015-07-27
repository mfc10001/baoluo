

struct PlayerFbData
{
    uint32 fb_idx;
	uint16 lastnum;		///< 最近一次的副本时间时，玩家的副本次数
    uint32 lastdate;
    uint8    fb_type;
    bool       ispass;
    uint8     feng;  ///< 评分

	PlayerFbData()
	{
		memset(this,0,sizeof(PlayerFbData));
	}
	
	PlayerFbData(uint8 _type) :fb_type(_type)
	{
	    ispass    = false;
	    feng = 48;
        lastdate = 0;
        lastnum  = 0;
	}
};



class GameFbDataManager
{
	typedef map<uint32 ,PlayerFbData> FbDataMap;
	FbDataMap m_fbdata;
	
	bool IsFbPass(const uint32 &fbidx);
    void AddFbdata(PlayerFbData fbdata);
    void AddFbdata(uint32 fbidx,uint8 fbtype,uint32 times = 0);
};


