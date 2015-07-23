
#ifndef _ISE_BASETYPE_H_
#define _ISE_BASETYPE_H_


#include <string>
using namespace std;

#define bcopy(src,dst,size)	memcpy(dst,src,size);

inline void bzero(void* Dest, int Count)
{
        memset(Dest,0,Count);
}



typedef vector<string> StrContaonType;
typedef vector<string>::iterator StrContaonTypeItr;


#define CheckCondition(cond, ret)\
	do{\
		if(!(cond))	\
		return (ret); \
	}while(0)

#define CheckConditionVoid(cond)\
	do{\
		if(!(cond))	\
		return; \
	}while(0)

#define LogCheckCondition(cond, ret, msg, ...)\
	do{\
		if(!(cond)){\
			ERROR(msg, ##__VA_ARGS__);\
			return (ret);\
		}\
	}while(0)

#define LogCheckConditionVoid(cond, msg, ...)\
	do{\
		if(!(cond)){\
			ERROR(msg, ##__VA_ARGS__);\
			return;\
		}\
	}while(0)

#ifndef DELETE_VALUE
#define DELETE_VALUE(x) \
			do{  \
				delete (x); \
				(x) = NULL; \
			}while(0) 
#endif
		
#ifndef DELETE_ARRAY
#define DELETE_ARRAY(x) \
			do{ \
				delete [] (x); \
				(x) = NULL; \
			}while(0)
#endif



enum ItemType
{
	ItemType_Common=0,
	ItemType_Equip=1,
};



#endif
