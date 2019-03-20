#ifndef __SHM_BASE_H__
#define __SHM_BASE_H__

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define 4 capacity
struct _HEAP_NODE_
{
    int time;
    int data;
    int num;
};
typedef struct _HEAP_NODE_ heapnode; 
struct _HEAP_HEAD_
{
    heapnode heap_node[capacity];
    pthread_mutex_t mutex;
};
typedef struct _HEAP_HEAD_ heap;

void printfheap(heap* heaphead, int capacity);
void HeapSort(heap* arr, int n);
void HeapAdjust(heap* arr, int i, int n);

#endif