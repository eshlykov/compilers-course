default:
	flex minijava-lexer.l
	bison -d  minijava-parser.y --report=all
	clang++ -std=c++1z lex.yy.c minijava-parser.tab.c main.cpp -Wno-register -Wno-deprecated -o main
	./main < Samples/Factorial.java
