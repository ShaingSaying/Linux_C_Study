#include<stdio.h>
#define SIZE 5
void copy_arr(double arrt1[],double arrs2[],int size);
void copy_ptr(double arrt2[],double arrs2[],int size);
void copy_ptrs(double arrt3[],double arrs3[],double *pp);
int main()
{
	int i=0;
	double *pp;
	double source[SIZE] = {1.1, 2.2, 3.3, 4.4, 5.5};
	double target1[SIZE];
    	double target2[SIZE];
	double target3[SIZE];
	pp=source;

	copy_arr(target1,source,SIZE);
	copy_ptr(target2,source,SIZE);
	copy_ptrs(target3,source,pp+SIZE-1);


	printf("Source Array:\n");
	for(i=0;i<SIZE;i++)
		printf("%.2f\t",source[i]);
	printf("\n");
	printf("target1 Array:\n");
        for(i=0;i<SIZE;i++)
                 printf("%.2f\t",target1[i]);
        printf("\n");
	printf("target2 Array:\n");
        for(i=0;i<SIZE;i++)
                 printf("%.2f\t",target2[i]);
        printf("\n");
	printf("target3 Array:\n");
        for(i=0;i<SIZE;i++)
                  printf("%.2f\t",target3[i]);
        printf("\n");


	return 0;
}
void copy_arr(double arrt1[],double arrs2[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		arrt1[i]=arrs2[i];
	}
}
void copy_ptr(double arrt2[],double arrs2[],int size)
{
	double *ptr;
	double *p=arrt2;
	for(ptr=arrs2;ptr<arrs2+size;ptr++,p++)
	{
		*p=*ptr;
	}

}
void copy_ptrs(double arrt3[],double arrs3[],double *pp)
{
	double *ptr;
	double *p=arrt3;
	for(ptr=arrs3;ptr<=pp;ptr++,p++)
	{
		*p=*ptr;	
	}

}
