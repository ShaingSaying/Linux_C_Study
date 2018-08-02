#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void trim(char *);

int main(void)
{
    const unsigned int SIZE = 128;
    char str[SIZE];

    while (true)
    {
        puts("Input a string(null string to quit):");
        fgets(str, SIZE, stdin);
        str[strlen(str) - 1] = '\0';

        if (*str != '\0')
        {
            trim(str);
            puts(str);
        }
        else
        {
            break;
        }
    }

    return 0;
}

void trim(char * str)
{
    char * p = str;
    char * q = str;

    while (*p != '\0' && *p != ' ')
    {
        p++;
    }

    if (' ' == *p)
    {
        q = p + 1;

        while (*q != '\0')
        {
            if (*q != ' ')
            {
                *p = *q;
                p++;
            }
            q++;
        }
    }
    *p = '\0';
}
