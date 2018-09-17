default:
	flex main.l
	g++ lex.yy.c -o main
	./main
