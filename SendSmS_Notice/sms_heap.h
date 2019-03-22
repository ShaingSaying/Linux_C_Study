#ifndef __SHM_HEAP_H__
#define __SHM_HEAP_H__

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

struct _HEAP_NODE_
{
    unsigned int time;
    int data;
    int num;
};
typedef struct _HEAP_NODE_ heapnode; 
struct _HEAP_HEAD_
{
    heapnode heap_node[4];
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
};
typedef struct _HEAP_HEAD_ heap;

void printfheap(heap* heaphead, int capacity);
void HeapSort(heap* arr, int n);
void HeapAdjust(heap* arr, int i, int n);

#endif