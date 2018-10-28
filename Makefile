default:
	flex lexer.l
	bison -d  parser.y --report=all
	clang++ -std=c++17 lex.yy.c parser.tab.c main.cpp -Wno-register -Wno-deprecated -o main
	./main < tests/samples-good/Factorial.java
	dot -T svg ast.dot -o ast.svg
