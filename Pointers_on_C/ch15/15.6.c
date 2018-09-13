extern int palindrome(int value)

int numberic_palindrome(int value)
{
    char string[50];

    sprintf(string,"%d",value);
    return palindrome(string);
}