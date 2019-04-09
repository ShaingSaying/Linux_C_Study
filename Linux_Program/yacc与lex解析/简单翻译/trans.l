/* 英式英语 -> 美式英语 */
%%
"colour"        { printf("color"); }
"flavour"       { printf("flavor"); }
"clever"        { printf("smart"); }
"smart"         { printf("elegant"); }
"conservative"  { printf("liberal"); }
.               { printf("%s", yytext); }
%%
main(int argc, char **argv)
{
    yylex();
}
int yywrap()
{
    return 1;
}