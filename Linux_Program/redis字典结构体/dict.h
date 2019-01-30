#include<stdio.h>

typedef struct dictEntry
{
    void *key;

    union 
    {
        void *val;
        uint64_t u64;
        int64_t s64;
    } v;
    
    struct dictEntry *next;
} dictEntry;

typedef struct dictht
{
    dictEntry **table;

    unsigned long size;

    unsigned long sizemask;

    unsigned long used;
} dictht;

typedef struct dictType
{
    //计算哈希值的函数
    unsigned int (*hashFunction)(const void *key);

    //复制键的函数
    void *(*keyDup)(void *privdata, const void *key);

    //复制值的函数
    void *(*valDup)(void *privdata, const void *obj);

    //对比键的函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);

    //销毁键的函数
    void (*keyDestructor)(void *privdata, void *key);

    //销毁值的函数
    void (*valDestructor)(void *privdata, void* obj);
} dictType;

//字典结构
typedef struct dict
{
    dictType *type;

    void *privdate;

    /*两个项的数组，每个项都是一个dictht哈希表,另一个是rehash的时候使用*/
    dictht ht[2];

    /*记录rehash的进度，如果没有进行rehash，值为-1*/
    int rehashidx;

    int iterators;
} dict;

