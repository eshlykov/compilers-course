default:
	bison main.y
	bison -d main.y
	flex main.l
	clang++ -std=c++17 lex.yy.c main.tab.c -Wno-register -o main
	./main < Factorial.java
