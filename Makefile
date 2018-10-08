default:
	bison -d main.y -o minijava-parser
	flex main.l
	clang++ -std=c++17 lex.yy.c -Wno-register -o main
	./main < Factorial.java
