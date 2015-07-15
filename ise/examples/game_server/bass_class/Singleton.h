
#ifndef _ISE_SINGLETON_H_
#define _ISE_SINGLETON_H_
#include "ise/main/ise.h"


class BaseConfig
{
public:
	uint32 id;
	uint32 getIndex(){return id;}
};


#endif
