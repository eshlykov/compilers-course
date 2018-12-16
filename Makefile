CC=clang++ -stdlib=libc++ -std=c++17 -Wno-register -Wno-deprecated
CPP = `find . -name "*cpp"`

compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	$(CC) $(CPP) -g -o compiler

default: compile
	python3 testlib/tester.py compiler

test: compile
	python3 testlib/tester.py compiler

draw: compile
	./testlib/test-folder-creation.sh
	python3 testlib/drawer.py compiler

leaks_check: compile
	python3 testlib/memory_leak_checker.py compiler

cppcheck:
	git clean -fdx > /dev/null
	cppcheck --enable=all -f $(CPP)

travis_compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	clang++ $(CPP) -std=c++17 -Wno-register -Wno-deprecated -o compiler

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
	cppcheck --enable=all -f $(CPP)

travis_leaks_check: compile
	python3 testlib/memory_leak_checker.py compiler

travis_all_checks: travis_test travis_draw travis_cppcheck travis_leaks_check