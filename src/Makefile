bcc:	parser.tab.c lex.yy.c classes.cpp classes.h
	g++ parser.tab.c classes.cpp -lfl -o bcc
parser.tab.c: parser.y 
	bison -d -v parser.y 
parser.tab.h: parser.y
	bison -d  parser.y 
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean 
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true
