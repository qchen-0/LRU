/*
* file name:	LRUCache.h
* desp:    		LRU cache interface
*/

#ifndef __LRUCACHE_H__
#define __LRUCACHE_H__

/*	Create LRU cache*/
int LRUCacheCreate(int capacity, void **lruCache);

/*	destory LRU cache*/
int LRUCacheDestory(void *lruCache);

/*put data into cache*/
int LRUCacheSet(void *lruCache, char key, char data);

/*get data from cache*/
char LRUCacheGet(void *lruCache, char key);

/*print data from cache order by time*/
void LRUCachePrint(void *lruCache);

#endif //__LRUCHACHE_H__
