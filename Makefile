default:
	flex++ main.l
	clang++ -std=c++14 lex.yy.cc -o main
	./main < Factorial.java
