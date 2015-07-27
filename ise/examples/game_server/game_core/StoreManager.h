#ifndef STOREMANAGER_H
#define STOREMANAGER_H
#include "ise/main/ise.h"

class StoreManager:public Singleton<StoreManager>
{
    public:
        uint32 buyGoods(uint32 &itemId,GamePlayer* player);




        //storeManager();
        //virtual ~storeManager();
    protected:
    private:
};

#endif // STOREMANAGER_H
