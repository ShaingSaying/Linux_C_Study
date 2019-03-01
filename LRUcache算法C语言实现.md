# LRU缓存淘汰算法
LRU(Least recently used，最近最少使用)算法根据数据的历史访问记录来进行淘汰数据，其核心思想是“如果数据最近被访问过，那么将来被访问的几率也更高”。
<!--more-->

常见的实现策略是:
1. 新数据插入到链表头部；
2. 每当缓存命中（即缓存数据被访问），则将数据移到链表头部；
3. 当链表满的时候，将链表尾部的数据丢弃。

存在一个问题：**命中时需要遍历链表**，找到命中的数据块索引，然后需要将数据移到头部，时间复杂度是O(N)。

未解决遍历带来的消耗，再此设计一种哈希表维护的双向链表结构，以减少寻找数据块时的时间消耗。
![LRUcache结构体设计](LRUcache.jpg)
如上图所示，**每个数据块拥有2个角度的身份，一个身份是缓存双向链表的成员，一个身份是哈希表成员**。

```c
/*定义LRU缓存的缓存单元*/
typedef struct cacheEntryS{
    char key;     /* 数据块的key */
    char data;    /* 数据块的data */

    struct cacheEntryS *hashListPrev;  /* 缓存哈希表指针，指向哈希链表的前一个元素 */
    struct cacheEntryS *hashListNext;  /* 缓存哈希表指针，指向哈希链表的后一个元素 */

    struct cacheEntryS *lruListPrev;   /* 缓存双向链表指针，指向链表的前一个元素 */
    struct cacheEntryS *lruListNext;   /* 缓存双向链表指针，指向链表的后一个元素 */
}cacheEntryS;

/* 定义LRU缓存*/ 
typedef struct LRUCacheS{
    int cacheCapacity;        /*缓存的容量*/
    cacheEntryS **hashMap;    /*缓存的哈希表*/

    cacheEntryS *lruListHead; /*缓存双向链表表头*/
    cacheEntryS *lruListTail; /*缓存双向链表表尾*/
    int lruListSize;          /*缓存双向链表节点个数*/
}LRUCacheS;
```
# 接口设计
## 双向链表相关接口设计
```c
/*从双向链表中删除指定节点*/
static void removeFromList(LRUCacheS *cache, cacheEntryS *entry)
{
    /*链表为空*/
    if (cache->lruListSize==0)
        return ;

    if (entry==cache->lruListHead && entry==cache->lruListTail) {
    /*链表中仅剩当前一个节点*/
        cache->lruListHead = cache->lruListTail = NULL;
    } else if (entry == cache->lruListHead) {
    /*欲删除节点位于表头*/
        cache->lruListHead = entry->lruListNext;
        cache->lruListHead->lruListPrev = NULL;
    } else if (entry == cache->lruListTail) {
    /*欲删除节点位于表尾*/
        cache->lruListTail = entry->lruListPrev;
        cache->lruListTail->lruListNext = NULL;
    } else {
    /*其他非表头表尾情况，直接摘抄节点*/
        entry->lruListPrev->lruListNext = entry->lruListNext;
        entry->lruListNext->lruListPrev = entry->lruListPrev;
    }
    /*删除成功，链表节点数减1*/
    cache->lruListSize--;
}
```
```c
/* 将节点插入到链表表头 */ 
static cacheEntryS * insertToListHead(LRUCacheS *cache, cacheEntryS *entry) 
{
    cacheEntryS *removedEntry = NULL;

    if (++cache->lruListSize > cache->cacheCapacity) {
    /* 如果缓存满了，即链表当前节点数已等于缓存容量，那么需要先删除链表表尾节点，即淘汰最久没有被访问到的缓存数据单元*/
        removedEntry = cache->lruListTail;
        removeFromList(cache, cache->lruListTail);   
    }

    if (cache->lruListHead==NULL&&cache->lruListTail==NULL) {
    /*如果当前链表为空链表*/
            cache->lruListHead = cache->lruListTail = entry;
    } else {
    /*当前链表非空，插入表头*/
            entry->lruListNext = cache->lruListHead;
            entry->lruListPrev = NULL;
            cache->lruListHead->lruListPrev = entry;
            cache->lruListHead = entry;
    }

    return removedEntry;
}
```
```c
/*辅助性接口，用于保证最近访问的节点总是位于链表表头*/
static void updateLRUList(LRUCacheS *cache, cacheEntryS *entry) 
{
    /*将节点从链表中摘抄*/
    removeFromList(cache, entry);
    /*将节点插入链表表头*/
    insertToListHead(cache, entry);
}
```
## 哈希表相关接口设计
```c
/*哈希函数*/
static int hashKey(LRUCacheS *cache, char key)
{
    return (int)key%cache->cacheCapacity;
}
```
```c
/*从哈希表获取缓存单元*/
static cacheEntryS *getValueFromHashMap(LRUCacheS *cache, int key) {
    /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *entry = cache->hashMap[hashKey(cache,key)];

    /*2.遍历查询槽内链表，找到准确的数据项*/
    while (entry) {
        if (entry->key == key)
            break;
        entry = entry->hashListNext;
    }

    return entry;
}
```
```c
/*向哈希表插入缓存单元*/
static void insertentryToHashMap(LRUCacheS *cache, cacheEntryS *entry) 
{
     /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *n = cache->hashMap[hashKey(cache, entry->key)];
    if (n!=NULL) {
    /*2.如果槽内已有其他数据项，将槽内数据项与当前欲加入数据项链成链表，当前欲加入数据项为表头*/
       entry->hashListNext = n;
       n->hashListPrev = entry;
    }
    /*3.将数据项放入加入哈希槽内*/
    cache->hashMap[hashKey(cache,entry->key)] = entry;
}
```
```c
/*从哈希表删除缓存单元*/
static void removeEntryFromHashMap(LRUCacheS *cache, cacheEntryS *entry) 
{
    /*无需做任何删除操作的情况*/
    if (NULL==entry || NULL==cache || NULL==cache->hashMap) return ;

    /*1.使用函数函数定位数据存放在哪个槽*/
    cacheEntryS *n = cache->hashMap[hashKey(cache,entry->key)];
    /*2.遍历槽内链表，找到欲删除节点，将节点从哈希表摘除*/
    while (n) {
        if (n->key==entry->key) {/*找到欲删除节点，将节点从哈希表摘抄*/
            if (n->hashListPrev) {
                n->hashListPrev->hashListNext = n->hashListNext;
            } else {
                cache->hashMap[hashKey(cache, entry->key)] = n->hashListNext;
            }
            if (n->hashListNext)
                n->hashListNext->hashListPrev = n->hashListPrev;
            return ;
        }
        n = n->hashListNext;
    }
}
```
## LRU接口设计
```c
/*将数据放入LRU缓存中*/
int LRUCacheSet(void *lruCache, char key, char data)
{
    LRUCacheS *cache = (LRUCacheS *)lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache, key);
    if (entry!=NULL) {/*数据已经在缓存中*/
    /*更新数据，将该数据项更新至链表表头*/
        entry->data = data;
        updateLRUList(cache, entry);
    } else {
    /*数据没在缓存中*/
       /*新建缓存单元*/
       entry = newCacheEntry(key, data);

       /*将新建缓存单元插入链表表头*/
       cacheEntryS *removedEntry = insertToListHead(cache, entry);
       if (NULL != removedEntry) {
       /*将新建缓存单元插入链表表头过程中，发生缓存满了的情况，需要淘汰最久没有被访问到的缓存数据单元*/
           removeEntryFromHashMap(cache, removedEntry);     
           freeCacheEntry(removedEntry);
       }
       /*将新建缓存单元插入哈希表*/
       insertentryToHashMap(cache, entry);
    }    
    return 0;
}
```
```c
/*从缓存中获取数据*/
char LRUCacheGet(void *lruCache, char key)
{
    LRUCacheS *cache = (LRUCacheS *)lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache,key);
    if (NULL != entry) {
        /*缓存中存在该数据，更新至链表表头*/
        updateLRUList(cache, entry);
        /*返回数据*/
        return entry->data;
    } else {
        /*缓存中不存在相关数据*/
        return '\0';
    }
}
```