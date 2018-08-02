#include <stdio.h>

unsigned int get_index_of_max(double [], unsigned int);

int main(void)
{
    const int SIZE = 5;
    double arr[SIZE] = {1.1, 2.2, 5.5, 3.3, 4.4};

    printf("Max index: %u\n", get_index_of_max(arr, SIZE));

    return 0;
}

unsigned int get_index_of_max(double arr[], unsigned int size)
{
    unsigned int i = 0;
    unsigned int max = 0;

    for (i = 1; i < size; i++)
    {
        if (arr[i] > arr[max])
        {
            max = i;
        }
    }

    return max;
}
