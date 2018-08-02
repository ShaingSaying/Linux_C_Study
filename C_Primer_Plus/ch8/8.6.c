#include <stdio.h>
#include <ctype.h>

char get_first(void);

int main(void)
{
    char ch;

    while ((ch = get_first()) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");

    return 0;
}

char get_first(void)
{
    char ch;

    while ( (ch = getchar()) && isspace(ch))		//如果是空白字符则返回真
    {
        continue;
    }

    return ch;
}
