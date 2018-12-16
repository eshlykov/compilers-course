CC=clang++ -stdlib=libc++ -std=c++17 -Wno-register -Wno-deprecated
CPP = `find . -name "*cpp"`

compile:
	flex -olexer.cpp lexer.l
	bison -o parser.cpp -d parser.y --report=all
	$(CC) $(CPP) -g -o compiler

default: compile
	python3 testlib/tester.py compiler

test: compile
	./testlib/test-folder-creation.sh
	python3 testlib/tester.py compiler

draw: compile
	python3 testlib/drawer.py compiler

leaks_check: compile
	python3 testlib/memory_leak_checker.py compiler

cppcheck:
	git clean -fdx > /dev/null
	cppcheck --enable=all -f $(CPP)

all_checks: test draw cppcheck leaks_check
