default:
	bison -d main.y -o minijava-parser
	flex main.l
	clang++ -std=c++17 lex.yy.c minijava-parser.h -Wno-register
	./a.out < Factorial.java
