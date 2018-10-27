default:
	flex lexer-minijava.l
	bison -d  parser-minihava.y --report=all
	clang++ -std=c++1z lex.yy.c parser-minijava.tab.c main.cpp -Wno-register -Wno-deprecated -o main
	./main < tests/samples-good/Factorial.java
