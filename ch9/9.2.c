#include <stdio.h>

void chline(char ch, int x, int y);

int main(void)
{
    char ch;
    int x, y;

    printf("Please input a char: ");
    ch = getchar();
    printf("Please input the coordinate to print: ");
    scanf("%d %d", &x, &y);
    chline(ch, x, y);
    printf("\n");
    return 0;
}

void chline(char ch, int x, int y)
{
    while(--x != 0)
    {
        putchar('\n');
    }
    while (--y != 0)
    {
        putchar(' ');
    }
    putchar(ch);
}
