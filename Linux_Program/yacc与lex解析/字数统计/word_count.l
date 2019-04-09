%{
/*[a-zA-Z]+   { words++; chars += strlen(yytext); }*/
/* 1.flex word_count.l 2.gcc lex.yy.c -Ifl*/
int chars = 0;
int words = 0;
int lines = 0;
%}
%%
/* 字符串 */
[^ \t\n\r\f\v]  { words++; chars += strlen(yytext); }
\n          { chars++; lines++; }
.           { chars++; }
%%

main(int argc, char *argv[])
{
    yylex();
    printf("lines:%4d\nwords:%4d\nchars:%4d\n", lines, words, chars);
}
int yywrap()
{
    return 1;
}

/* flex word_count.l
gcc lex.yy.c -Ifl */