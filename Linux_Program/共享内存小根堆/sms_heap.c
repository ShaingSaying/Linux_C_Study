#include "sms_heap.h"

void HeapAdjust(heap* arr, int i, int n)
{
    int nChild;
    heapnode tmp;
    for(;2*i+1<n;i=nChild)
    {
        nChild=2*i+1;
        if(nChild<n-1 && arr->heap_node[nChild+1].time > arr->heap_node[nChild].time)
            ++nChild;
        if(arr->heap_node[i].time < arr->heap_node[nChild].time)
        {
            tmp=arr->heap_node[i];
            arr->heap_node[i]=arr->heap_node[nChild];
            arr->heap_node[nChild]=tmp;
        }
        else
            break;
    }
}
void HeapSort(heap* arr, int n)
{
    int i;
    heapnode tmp;
    //对序列中的每个非叶子节点执行调整算法，使该序列成为一个堆
    for(i=(n-1)/2;i>=0;i--)
        HeapAdjust(arr, i, n);
    //从最后一个元素开始对序列进行调整，不断缩小调整的范围直到第一个元素
    for(i=n-1;i>0;i--)
    {
        //把第一个元素和当前的最后一个元素交换
        //保证当前最后一个位置存放的是现在这个序列中最大的元素
        tmp =arr->heap_node[0];
        arr->heap_node[0] = arr->heap_node[i];
        arr->heap_node[i] = tmp;
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(arr, 0, i);
    }
}

void printfheap(heap* heaphead, int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
    {
        printf("time:%d data:%d num:%d\n",heaphead->heap_node[i].time,heaphead->heap_node[i].data,heaphead->heap_node[i].num);
    }
}
