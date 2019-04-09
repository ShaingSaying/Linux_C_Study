/* 识别出用于计算机的记号并把它们输出 */
%{
    enum yytokentype {
        NUMBER = 258,
        ADD    = 259,
        SUB    = 260,
        MUL    = 261,
        DIV    = 262,
        ABS    = 263,
        EOL    = 264
    };
    int yylval;
%}
%%
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"|"         { return ABS; }
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
\n          { return EOL; }
[ \t]       { /* 忽略空白字符 */ }
.           { printf("Mystery character %s\n", yytext); }
%%
main(int argc, char **argv)
{
    int tok;

    while(tok = yylex()){
        printf("%d", tok);
        if(tok == NUMBER)
            printf(" = %d\n", yylval);
        else
            printf("\n");
    }
}

int yywrap()
{
    return 1;
}
