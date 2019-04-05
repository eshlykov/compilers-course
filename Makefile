CC=clang++ -std=c++17 -Wno-register -Wno-deprecated
CPP = `find src -name "*cpp"`
SOURCES = `find src -name "*cpp" -not -name "parser.cpp" -not -name "lexer.cpp"`

compile:
	flex -osrc/lexer.cpp src/lexer.l
	bison -o src/parser.cpp -d src/parser.y --report=all
	$(CC) $(CPP) -g -o compiler

leaks_check: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./compiler $(TEST)

test: compile
	python3 testlib/tester.py compiler

draw: compile
	./testlib/test-folder-creation.sh
	python3 testlib/drawer.py compiler

full_leaks_check: compile
	python3 testlib/memory-leak-checker.py compiler

cppcheck:
	cppcheck --enable=all -f $(SOURCES)

travis_all_checks: test draw cppcheck full_leaks_check
