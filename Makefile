default:
	flex lexer.l
	bison -d  parser.y --report=all
	clang++ -std=c++1z lex.yy.c parser.tab.c main.cpp -Wno-register -Wno-deprecated -o main
	./main < tests/samples-good/Factorial.java
