CC=clang++ -stdlib=libc++ -std=c++17 -Wno-register -Wno-deprecated
CPP = `find . -name "*cpp"`
PP = `find . -name "*pp"`

default:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	$(CC) $(CPP) -o compiler
	python3 testlib/tester.py compiler

compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	$(CC) $(CPP) -o compiler

test: compile
	python3 testlib/tester.py compiler

draw: compile
	./testlib/test-folder-creation.sh
	python3 testlib/drawer.py compiler

leaks_check: compile
	python3 testlib/tester.py valgrind --leak-check=full \
                                       --show-leak-kinds=all \
                                       --track-origins=yes \
                                       ./compiler
cppcheck:
	git clean -fdx > /dev/null
	cppcheck --enable=all -f $(PP)

travis_compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	g++ $(CPP) -std=c++17 -Wno-register -Wno-deprecated -o compiler

travis: travis_compile
	python3 testlib/tester.py compiler
	dot -T svg ast.dot -o ast.svg

travis_test: travis_compile
	./testlib/test-folder-creation.sh
	python3 testlib/tester.py compiler

travis_draw: travis_compile
	python3 testlib/drawer.py compiler

travis_cppcheck:
	git clean -fdx > /dev/null
	cppcheck --enable=all -f $(PP)

travis_all_checks: travis_test travis_draw travis_cppcheck
