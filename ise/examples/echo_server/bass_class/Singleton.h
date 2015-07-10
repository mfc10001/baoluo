
#ifndef _ISE_SINGLETON_H_
#define _ISE_SINGLETON_H_
#include "ise/main/ise.h"


class Singleton
{
private:
	Singleton()   //���캯����˽�е�
	{
	}
	static Singleton *m_pInstance;
public:
	static Singleton * getInstance()
	{
		if(m_pInstance == NULL)  //�ж��Ƿ��һ�ε���
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
