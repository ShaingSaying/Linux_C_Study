/* 识别出用于计算机的记号并把它们输出 */
%{
#include "count.tab.h"
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
