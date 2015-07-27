#ifndef STOREMANAGER_H
#define STOREMANAGER_H
#include "ise/main/ise.h"
#include "GamePlayer.h"

class StoreManager:public Singleton<StoreManager>
{
    public:
        uint32 buyGoods(uint32 &goodsId,GamePlayer *player);

        StoreManager();
        virtual ~StoreManager();
    protected:
    private:
        friend class Singleton<StoreManager>;
};

#endif // STOREMANAGER_H
