count: symbol.l count.y
	bison -d count.y
	flex symbol.l
	cc -o $@ count.tab.c lex.yy.c -lfl