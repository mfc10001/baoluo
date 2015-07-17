#include "ise/main/ise.h"


struct Entry : private Noncopyable
{
	public: 
		union
		{
			uint32 id;
			struct
			{
				uint16 wid1; 
				uint16 wid2; 
			};
			struct
			{
				uint8 cid1; 
				uint8 cid2; 
				uint8 cid3; 
				uint8 cid4; 
			};
		};
		union
		{
			uint32 tempid;
			struct
			{
				uint16 tempid1;
				uint16 tempid2;
			};
		};
		char name[MAX_NAMESIZE];
		Entry();
		Entry(const uint32 id, const char* name);
		virtual ~Entry();
		uint32 getEntryID() const;
		virtual const char *getClassName() const = 0;
		const Entry* setLogHead(const char* file, const uint32& line) const;
		typedef std::set<Entry*> PointMap;
		typedef PointMap::iterator PointMap_iter;

		bool debug(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool error(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool info(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool fatal(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool warn(const char * pattern, ...) const __attribute__((format(printf,2,3)));
		bool trace(const char * pattern, ...) const __attribute__((format(printf,2,3)));
};

