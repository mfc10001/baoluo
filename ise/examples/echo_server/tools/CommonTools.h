#ifndef _ISE_COMMONTOOLS_H_
#define _ISE_COMMONTOOLS_H_



#include<stdio.h>
#include<string.h>
#include "../game_define/BaseType.h"

class CommonTools{
public:
    //根据 "1,2,3" 获得数字数组
    static int *split(char * str,const char *split,const int count){
        if(strlen(str)==0 || strlen(split)==0)
            return NULL;
        if(count <=1) return NULL;
        int * ints=new int[count];
        memset(ints,0x0,count*sizeof(int));
        
        char split_str[48];
        int index_length=0;
        
        snprintf(split_str,48,"%%d%s",split);
        for (int i=0;i<count;i++){
            sscanf(str+index_length,split_str,&ints[i]);
            char num_str[20]={0};
            sprintf(num_str,"%d",ints[i]);
            index_length+=strlen(num_str)+strlen(split);
        }
        return ints;
    }
    //根据数字数组 组合为字符串
    static char * bindNumbersToStr(int * nums,const unsigned int  nums_length,const char * split){
        char * str=new char[1025];
        char num_str[20]={0};
        int index_length=0;
        for(int i=0;i<nums_length;i++){
            sprintf(str+index_length,"%d%s",nums[i],split);
            index_length=strlen(str);
        }
        str[index_length-strlen(split)]=0x0;
        return str;
    }



	static void split(string const& str, string const& delimiter, StrContaonType& dest)
	{
	    size_t pos = 0, found = 0;

	    while ( found != string::npos )
	    {
	        found = str.find(delimiter, pos);
	        dest.push_back(string(str, pos, found - pos));
	        pos = found + 1;
	    }

	}
};

#endif
