
#ifndef _ISE_BASETYPE_H_
#define _ISE_BASETYPE_H_


#include <string>
using namespace std;

#define bcopy(src,dst,size)	memcpy(dst,src,size);

inline void bzero(void* Dest, int Count)
{	
	__asm
	{
		mov		ecx, [Count]
			mov		edi, [Dest]
			xor     eax, eax
			mov		edx, ecx
			shr		ecx, 2
			and		edx, 3
			rep     stosd
			mov     ecx, edx
			rep     stosb
	}
}



typedef vector<string> StrContaonType;
typedef vector<string>::iterator StrContaonTypeItr;




#endif
