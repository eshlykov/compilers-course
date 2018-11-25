CPP = `find . -name "*cpp"`

default:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ $(CPP) -std=c++17 -stdlib=libc++ -Wno-register -Wno-deprecated -o compiler
	python3 testlib/tester.py compiler

compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ $(CPP) -std=c++17 -stdlib=libc++ -Wno-register -Wno-deprecated -o compiler

travis:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++ $(CPP) -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 testlib/tester.py compiler
	dot -T svg ast.dot -o ast.svg

travis_test:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++ $(CPP) -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 testlib/tester.py compiler

travis_draw:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++ $(CPP) -std=c++17 -Wno-register -Wno-deprecated -o compiler
	python3 testlib/drawer.py compiler

test:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ $(CPP) -std=c++17 -stdlib=libc++ -Wno-register -Wno-deprecated -o compiler
	python3 testlib/tester.py compiler

draw:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ $(CPP) -std=c++17 -stdlib=libc++ -Wno-register -Wno-deprecated -o compiler
	python3 testlib/drawer.py compiler
