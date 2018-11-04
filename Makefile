default:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ -std=c++1z lexer.cpp parser.cpp main.cpp -Wno-register -Wno-deprecated -o compiler
	./compiler < tests/samples-good/BinarySearch.java
	dot -T svg ast.dot -o ast.svg
