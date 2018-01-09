/*
* file name:	main.c
* desp:    		LRU Cache test
*/

#include <stdio.h>
#include <stdlib.h>
#include "LRUCache.h"

/*error handle macro*/
#define HANDLE_ERROR(msg) \
		do{\
			fprintf(stderr, "%s fail.\n", msg); \
			exit(-1); \
		} while(0)

#define LRUCACHE_PUTDATA(cache, data) \
		do{\
			if(0 != LRUCacheSet(cache, data, data)) \
				fprintf(stderr, "put(%c,%c) to cache fail.\n", data, data);\
			else \
				fprintf(stdout,"put(%c,%c) to cache sucess.\n",data, data);\
		}while(0)

#define LRUCACHE_GETDATA(cache, key) \
		do{\
			char data = LRUCacheGet(cache, key);\
			if('\0' == data) \
				fprintf(stderr, "get(Key:%c) from cache fail.\n", key);\
			else \
				fprintf(stdout, "get(Key:%c) from cache sucess.\n", key);\
		}while(0)

/*	test 1*/
void testcase1(void)
{
	fprintf(stdout,"====================\n");
	fprintf(stdout,"In testcase1........\n");
	fprintf(stdout,"====================\n");

	void* lruCache;
	if(0 != LRUCacheCreate(5, &lruCache))
		HANDLE_ERROR("LRUCacheCreate");
	
	/*ABC!*/
	LRUCACHE_PUTDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_PUTDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'B');
	LRUCACHE_PUTDATA(lruCache, 'C');
	LRUCACHE_GETDATA(lruCache, 'C');

	LRUCachePrint(lruCache);

	/*DEAF*/
	LRUCACHE_PUTDATA(lruCache, 'D');
	LRUCACHE_GETDATA(lruCache, 'D');
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_GETDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_PUTDATA(lruCache, 'F');
	LRUCACHE_GETDATA(lruCache, 'F');

	LRUCachePrint(lruCache);


	/*B*/
	LRUCACHE_PUTDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'B');

	if(0 != LRUCacheDestory(lruCache))
		HANDLE_ERROR("LRUCacheDestory");
	
	fprintf(stdout, "\n\ntestcase1 finishede \n");
	fprintf(stdout, "========================\n\n");
}

/*testcase2*/
void testcase2(void)
{
	fprintf(stdout,"====================\n");
	fprintf(stdout,"In testcase2........\n");
	fprintf(stdout,"====================\n");

	void* lruCache;
	if(0 != LRUCacheCreate(3, &lruCache))
		HANDLE_ERROR("LRUCacheCreate");

	/*wxwyz!*/
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'Z');

	LRUCachePrint(lruCache);

	LRUCACHE_PUTDATA(lruCache, 'Z');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'W');

	LRUCachePrint(lruCache);

	/*yzwyx*/
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'Z');
	LRUCACHE_PUTDATA(lruCache, 'W');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'X');
	
	LRUCachePrint(lruCache);
	
	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'W');
	LRUCACHE_GETDATA(lruCache, 'Z');
	LRUCACHE_GETDATA(lruCache, 'Y');

	LRUCachePrint(lruCache);

	/*xyxy!*/
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'Y');
	LRUCACHE_PUTDATA(lruCache, 'X');
	LRUCACHE_PUTDATA(lruCache, 'Y');

	LRUCachePrint(lruCache);
	
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'X');
	LRUCACHE_GETDATA(lruCache, 'Y');
	LRUCACHE_GETDATA(lruCache, 'X');

	LRUCachePrint(lruCache);

	if(0 != LRUCacheDestory(lruCache))
		HANDLE_ERROR("LRUCacheDestory");
	fprintf(stdout, "\n\ntestcase2 finished.....\n");
	fprintf(stdout, "==============================\n\n");
}

/*testcase3*/
void testcase3(void)
{
	fprintf(stdout,"====================\n");
	fprintf(stdout,"In testcase1........\n");
	fprintf(stdout,"====================\n");
	
	void* lruCache;
	if(0 != LRUCacheCreate(5, &lruCache))
		HANDLE_ERROR("LRUCacheCreate");
	
	/*EIEIO*/
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'I');
	LRUCACHE_PUTDATA(lruCache, 'E');
	LRUCACHE_PUTDATA(lruCache, 'I');
	LRUCACHE_PUTDATA(lruCache, 'O');

	LRUCachePrint(lruCache);

	LRUCACHE_GETDATA(lruCache, 'A');
	LRUCACHE_GETDATA(lruCache, 'I');
	LRUCACHE_GETDATA(lruCache, 'B');
	LRUCACHE_GETDATA(lruCache, 'O');
	LRUCACHE_GETDATA(lruCache, 'C');
	LRUCACHE_PUTDATA(lruCache, 'A');

	LRUCachePrint(lruCache);

	if(0 != LRUCacheDestory(lruCache))
		HANDLE_ERROR("LRUCacheDestory");
	
	fprintf(stdout, "\n\ntestcase3 finished....\n");
	fprintf(stdout, "===============================\n\n");
}

int main()
{
	testcase1();
	testcase2();
	testcase3();

	return 0;
}

