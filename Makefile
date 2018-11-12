travis:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++ lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 tester.py compiler
	dot -T svg ast.dot -o ast.svg

travis_test:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 tester.py compiler

travis_draw:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 drawer.py compiler

test:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 tester.py compiler

draw:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++  lexer.cpp parser.cpp main.cpp -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 drawer.py compiler
