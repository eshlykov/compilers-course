default:
	flex minijava-lexer.l
	bison -d minijava-parser.y
	clang++ -std=c++17 lex.yy.c minijava-parser.tab.c main.cpp -Wno-register -Wno-deprecated -o main
	./main < Samples/Factorial.java
