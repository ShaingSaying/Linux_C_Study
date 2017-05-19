#include <stdio.h>
int main()
{
    char ch;
    int i = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch >= ' ')
        {
            printf("%-5c", ch);
        }
        else if (ch == '\n')
        {
            printf("%-5s", "\\n");
        }
        else if (ch == '\t')
        {
            printf("%-5s", "\\t");
        }
        else
        {
            printf("^%-4c", ch + 64);
        }
        printf("%-5d", ch);

        i++;
        if (i % 10 == 0)
        {
            i = 0;
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}
