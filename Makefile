default:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 checker.py compiler
	dot -T svg ast.dot -o ast.svg

test:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 tester.py compiler