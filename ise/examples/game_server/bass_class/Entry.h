#ifndef _ISE_ENTRY_H_
#define _ISE_ENTRY_H_
#include "ise/main/ise.h"

#include "../game_define/Protocol.h"

class Entry : private boost::noncopyable
{
	public:

		Entry(){};
		/*
		Entry(const uint32 id, const char* name)
		{
            this->id=id;
            memcpy(this->name,name,MAX_NAMESIZE);
		};
		*/
		~Entry(){};
		uint32 getEntryID() const
		{
            return id;
		};
		const char* getEntryName() const
		{
            return name;
		};
		//virtual const char *getClassName() const = 0;
		//const Entry* setLogHead(const char* file, const uint32& line) const;
		//typedef std::set<Entry*> PointMap;
	//  typedef PointMap::iterator PointMap_iter;


        uint32 id;
		char name[MAX_NAMESIZE];
/*
		bool debug(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool error(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool info(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool fatal(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool warn(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool trace(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		*/
};


#endif

