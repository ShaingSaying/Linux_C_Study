#include <stdio.h>
#include <string.h>

void reverse_string(char *);

int main(void)
{
    const unsigned int SIZE = 128;
    char str[SIZE];
    char ch;

    do
    {
        puts("Input a string:");
        fgets(str, SIZE, stdin);
        str[strlen(str) - 1] = '\0';

        puts("After Reverse:");
        reverse_string(str);
        puts(str);
        
        puts("Enter any key except q to go on.");
        ch = getchar();
    } while (ch != 'q');

    return 0;
}

void reverse_string(char * str)
{
    unsigned int i, j;
    char temp;
    i = 0;
    j = strlen(str) - 1;

    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
