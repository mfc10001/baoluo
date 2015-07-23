




class EquipImprove
{
	public:
		EquipImprove(GamePlayer *player); 
		~EquipImprove(); 

		uint32 strengthenEquip(uint8 pos);

		bool cost(GameItem* item);
		
	private:
		//@brief	属主
		GamePlayer* m_owner;
				
};

