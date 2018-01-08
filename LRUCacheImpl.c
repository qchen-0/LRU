#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LRUCache.h"
#include "LRUCacheImpl.h"

static void freeList(LRUCacheS* cache);

/**************************************
*LRU cache unit interface
**************************************/

/*create cacheunit */
static cacheEntryS* newCacheEntry(char key, char data)
{
	cacheEntryS* entry;
	if(NULL == (entry = malloc(sizeof(*entry)))){
		perror("malloc");
		return NULL;
	}
	
	memset(entry, 0, sizeof(*entry));
	entry->key = key;
	entry->data = data;
	
	return entry;
}

/*free cacheunit */
static void freeCacheEntry(cacheEntryS* entry)
{
	if(NULL == entry)
		return;
	free(entry);
}

/*LRUCreate */
int LRUCacheCreat(int capacity, void **lruCache)
{
	LRUCacheS* cache = NULL;
	if(NULL == (cache=malloc(sizeof(*cache)))){
		perror("malloc");
		return -1;
	}

	memset(cache, 0, sizeof(*cache));
	cache->capacity = capacity;
	cache->hashMap = (cacheEntryS**)malloc(sizeof(cacheEntryS)*capacity);
	if(NULL == cache->hashMap){
		free(cache);
		perror("malloc");
		return -1;
	}
	memset(cache->hashMap, 0, sizeof(cacheEntryS)*capacity);
	*lruCache = cache;
	return 0;
}

/*destory cache*/
int LRUCacheDestory(void* lruCache)
{
	LRUCacheS* cache = (LRUCacheS*)lruCache;
	if(NULL == cache)
		return 0;
	
	if(cache->hashMap)
		free(cache->hashMap);
	freeList(cache);
	free(cache);
	return 0;
}


/********************************************
*double list interface
********************************************/

static void removeFromList(LRUCacheS* cache, cacheEntryS* entry)
{
	if(cache->lruListSize == 0)
		return;
	if(entry == cache->lruListHead && entry == cache->lruListTail){
		cache->lruListHead = cache->lruListTail = NULL;
	}else if(entry == cache->lruListHead){
		cache->lruListHead = entry->lruListNext;
		cache->lruListHead->lruListPrev = NULL;
	}else if(entry == cache->lruListTail){
		cache->lruListTail = entry->lruListPrev;
		entry->lruListPrev->lruListNext = NULL;
	}else{
		entry->lruListPrev->lruListNext = entry->lruListNext;
		entry->lruListNext->lruListPrev = entry->lruListPrev;
	}

	--cache->lruListSize;
}

static cacheEntryS* insertToListHead(LRUCacheS* cache, cacheEntryS* entry)
{
	cacheEntryS* removeEntry = NULL;
	
	if(++cache->lruListSize >cache->capacity){
		removeEntry = cache->lruListTail;
		removeFromList(cache, cache->lruListTail);
	}

	if(cache->lruListSize == 0){
		cache->lruListHead = cache->lruListTail = entry;
	}else{
		entry->lruListNext = cache->lruListHead;
		entry->lruListPrev = NULL;
		cache->lruListHead->lruListPrev = entry;
		cache->lruListHead = entry;
	}

	return removeEntry;
}

static void freeList(LRUCacheS* cache)
{
	if(0 == cache->lruListSize) return;
	cacheEntryS* entry = cache->lruListHead;
	while(entry){
		cacheEntryS* temp = entry->lruListNext;
		freeCacheEntry(entry);
		entry = temp;
	}
	cache->lruListSize = 0;
}

static void updataLRUList(LRUCacheS* cache, cacheEntryS* entry)
{
	removeFromList(cache, entry);
	insertToListHead(cache, entry);
}


/*************************************************************
*hashmap interface
*************************************************************/
/*hash function*/
static int hashKey(LRUCacheS* cache, char key)
{
	return (int)key%(cache->capacity);
}

/*get value from hashmap*/
static cacheEntryS* getValueFromHashMap(LRUCacheS* cache, char key)
{
	cacheEntryS* entry = cache->hashMap[hashKey(cache,key)];

	while(entry){
		if(entry->key == key)
			break;
		entry = entry->hashListNext;
	}

	return entry;
}

/*insert entry to hashmap*/
static void insertEntryToHashMap(LRUCacheS* cache, cacheEntryS* entry)
{
	cacheEntryS* n = cache->hashMap[hashKey(cache, entry->key)];

	if(n != NULL){
		entry->hashListNext = n;
		n->hashListPrev = entry;
	}

	cache->hashMap[hashKey(cache, entry->key)] = entry;
}

/*remove entry from hashmap*/
static void removeEntryFromHashMap(LRUCacheS* cache, cacheEntryS* entry)
{
	if(cache == NULL || entry == NULL || cache->hashMap == NULL) return;

	cacheEntryS* n = cache->hashMap[hashKey(cache, entry->key)];

	while(n){
		if(n->key == entry->key){
			if(n->hashListPrev){
				n->hashListPrev->hashListNext = n->hashListNext;
			}else{
				cache->hashMap[hashKey(cache, entry->key)]=n->hashListNext;
			}
			if(n->hashListNext)
				n->hashListNext->hashListPrev = n->hashListPrev;
			return;
		}
		n = n->hashListNext;
	}
}

/*cache set/get interface*/
int LRUCacheSet(void* lruCache, char key, char data)
{
	LRUCacheS* cache = (LRUCacheS*) lruCache;
	cacheEntryS* entry = getValueFromHashMap(cache,key);
	if(entry != NULL){
		entry->data = data;
		updateLRUList(cache,entry);
	}else{
		entry = newCacheEntry(key,data);
		cacheEntryS* removeEntry = insertToListHead(cache,entry);

		if(NULL != removeEntry){
			removeFromHashMap(cache,removeEntry);
			freeCacheEntry(removeEntry);
		}
		insertEntryToHashMap(cache, entry);
	}

	return 0;
}

char LRUCacheGet(void* lruCache, char key)
{
	LRUCacheS* cache = (LRUCacheS*)lruCache;

	cacheEntryS* entry = getValueFromHashMap(cache,key);
	if(entry != NULL){
		updateLRUList(cache,entry);
		return entry->data;
	}else{
		return '\0';
	}
}

/*print*/
void LRUCachePrint(void* lruCache)
{
	LRUCacheS* cache = (LRUCacheS*)lruCache;
	if(cache == NULL || cache->lruListSize == 0) return;
	
	fprint(stdout,"\n>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	fprint(stdout,"cache   (key   data):\n");
	cacheEntryS* entry = cache->lruListHead;
	while(entry){
		fprint(stdout,"(%c  %c) ",entry->key, entry->data);
		entry = entry->lruListNext;
	}
	fprint(stdout,"\n<<<<<<<<<<<<<<<<<<<<<<<<\n");
}
