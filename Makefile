default:
	flex lexer.l
	bison -d  parser.y --report=all
	clang++ -std=c++1z lex.yy.c parser.tab.c main.cpp -Wno-register -Wno-deprecated -o compiler
	./compiler < tests/samples-good/Factorial.java
	dot -T svg ast.dot -o ast.svg
