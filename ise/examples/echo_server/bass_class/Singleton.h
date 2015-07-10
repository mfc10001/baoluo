
#ifndef _ISE_SINGLETON_H_
#define _ISE_SINGLETON_H_
#include "ise/main/ise.h"


class Singleton
{
private:
	Singleton()   //构造函数是私有的
	{
	}
	static Singleton *m_pInstance;
public:
	static Singleton * getInstance()
	{
		if(m_pInstance == NULL)  //判断是否第一次调用
			m_pInstance = new Singleton();
		return m_pInstance;
	}
};

class BaseConfig
{
	uint32 id;
	uint32 getIndex(){return id;}
};


#endif
