/*
*filename: LRUCacheImpl.h
*desp    : LRU cache datastructure
*/

#ifndef __LRUCACHEIMPL_H__
#define __LRUCACHEIMPL_H__

/*define cache cacheunit*/
typedef struct cacheEntryS
{
	char key;		//key of data
	char data;		//data
	struct cacheEntryS *hashListPrev; //cache of hash,pointer to the prev
	struct cacheEntryS *hashListNext; //cache of hash,pointer to the next

	struct cacheEntryS *lruListPrev; //doubleforward list,pointer to the prev
	struct cacheEntryS *lruListNext; //doubleforward list,pointer to the next
}cacheEntryS;

/*define LRU cache*/
typedef struct LRUCacheS
{
	int capacity;
	cacheEntryS ** hashMap;

	cacheEntryS *lruListHead;
	cacheEntryS *lruListTail;

	int lruListSize;
}LRUCacheS;

#endif //_LRUCACHEIMPL_H__
