#ifndef STOREMANAGER_H
#define STOREMANAGER_H
#include "ise/main/ise.h"

class storeManager:public Singleton<storeManager>
{
    public:
        uint32 buyGoods(uint32 &itemId);




        //storeManager();
        //virtual ~storeManager();
    protected:
    private:
};

#endif // STOREMANAGER_H
