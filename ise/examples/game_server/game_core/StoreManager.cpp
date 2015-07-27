#include "StoreManager.h"
#include "ConfigManager.h"
#include "../game_define/EntryBase.h"
#include "GamePlayer.h"
#include "GameItemManager.h"
#include "../game_define/ItemBase.h"
#include "../game_define/Protocol.h"

uint32 StoreManager::buyGoods(uint32 &goodsId,GamePlayer *player)
{
    const StoreDataEntry* goodsData = ConfigManager::instance().getStoreData(goodsId);
     if(goodsData)
     {
         uint32 money;
         money = player->getMoney(MoneyType_Diamond);
        if(money>=goodsData->price)
        {
           bool isSuccess = ItemCreator::autoUnionCreateItem(0 ,goodsId,1,player,AddItemAction_Store);

           if(isSuccess)
           {
               return ERR_SUCCESS;

           }else{
               return ERR_PACK_NULL;
           }
           player->subMoney(MoneyType_Diamond,goodsData->price,DelMoneyAction_Store);
        }else
        {
            return ERR_DIAMOND_LACK;
        }

     }else
     {
         return ERR_ITEM_NULL;
     }

}

StoreManager::StoreManager()
{
    //ctor
}

StoreManager::~StoreManager()
{
    //dtor
}
