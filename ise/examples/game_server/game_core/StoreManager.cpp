#include "StoreManager.h"
#include "ConfigManager.h"
#include "EntryBase.h"
#include "GamePlayer.h"
#include "GameItemManager.h"
#include "ItemBase.h"
#include "Protocol.h"

uint32 storeManager::buyGoods(uint32 &goodsId,GamePlayer *player)
{
     StoreDataEntry *GoodsData = ConfigManager::instance().getStoreData(goodsId);
     if(itemData)
     {
         int32 money;
         money = player->getMoney(MoneyType_Diamond)
        if(money>=GoodsData.price)
        {
           bool isSuccess = ItemCreator::autoUnionCreateItem(0,goodsId,1,player,AddItemAction_Store);
           if(!isSuccess)
           {
               return ERR_PACK_NULL;
           }

        }else
        {
            return ERR_DIAMOND_LACK;
        }

     }else
     {
         return ERR_ITEM_NULL;
     }

}

storeManager::storeManager()
{
    //ctor
}

storeManager::~storeManager()
{
    //dtor
}
