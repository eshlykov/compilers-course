default:
	bison -d main.y -o minijava-parser
	flex++ main.l
	clang++ -std=c++14 lex.yy.cc -o main
	./main < Factorial.java
