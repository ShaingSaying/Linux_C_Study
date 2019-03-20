#include "shm_base.h"

heap *creatHeap(int capacity)
{
    heap *ptr;
    ptr = (heap*)malloc(sizeof(heap));
    if(ptr==NULL)
        printf("malloc error\n");
    memset(ptr.heap_node,0x00,sizeof(heap.heap_node));
    return ptr;
}

void HeapAdjust(heap* arr, int i, int n)
{
    int nChild;
    heap tmp;
    for(;2*i+1<n;i=nChild)
    {
        nChild=2*i+1;
        if(nChild<n-1 && arr[nChild+1].time > arr[nChild].time)
            ++nChild;
        if(arr[i].time < arr[nChild].time)
        {
            tmp=arr[i];
            arr[i]=arr[nChild];
            arr[nChild]=tmp;
        }
        else
            break;
    }
}
void HeapSort(heap* arr, int n)
{
    int i;
    heap tmp;
    //对序列中的每个非叶子节点执行调整算法，使该序列成为一个堆
    for(i=(n-1)/2;i>=0;i--)
        HeapAdjust(arr, i, n);
    //从最后一个元素开始对序列进行调整，不断缩小调整的范围直到第一个元素
    for(i=n-1;i>0;i--)
    {
        //把第一个元素和当前的最后一个元素交换
        //保证当前最后一个位置存放的是现在这个序列中最大的元素
        //arr[i].time=arr[0].time^arr[i].time;
        //arr[0].time=arr[0].time^arr[i].time;
        //arr[i].time=arr[0].time^arr[i].time;
        tmp =arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(arr, 0, i);
    }
}

void printfheap(heap* heaphead, int capacity)
{
    int i;
    for(i=0;i<capacity;i++)
    {
        printf("time:%d\tdata:%d\tnum:%d\n",heaphead[i].time,heaphead[i].data,heaphead[i].num);
    }
}

int main(int argc, char **argv)
{
    int capacity;
    int i;
    heap *heaphead=NULL;

    capacity = atoi(argv[1]);

    create_shm(char *keyfile, sizeof())

    heaphead=creatHeap(capacity);
    printf("init heap:\n");
    printfheap(heaphead,capacity);
    for(i=0;i<capacity;i++)
    {
        scanf("%d %d %d",&heaphead[i].time,&heaphead[i].data,&heaphead[i].num);
    }
    printf("raw data:\n");
    printfheap(heaphead,capacity);

    HeapSort(heaphead,capacity);
    printf("heap data:\n");
    printfheap(heaphead,capacity);

    while(1)
    {
        sleep(5);
        if(heaphead[0].time > 5)
        {
            heaphead[0].time = 0;
            heaphead[0].data = 0;
            heaphead[0].num = 0;
            HeapSort(heaphead,capacity);
            printf("while heap data:\n");
            printfheap(heaphead,capacity);
        }
        if(heaphead[0].time <=5 )
            break;
    }
    printf("process over\n");
    return 0;
}
