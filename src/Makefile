CC=gcc
FLAGS =-Wall -Wextra -Werror -std=c11
FLAGS_GCOV =-fprofile-arcs --coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lcheck -lsubunit -lpthread -lrt -lm -g 
else
  LIBS=-lcheck 
endif

all: install run

run: install
	build/Calculator.app/Contents/MacOS/Calculator

tests:
	checkmk clean_mode=1 SmartCalc_v1.0_test.check > SmartCalc_v1.0_test.c
	$(CC) $(FLAGS_GCOV) SmartCalc_v1.0_test.c SmartCalc_v1.0.c $(LIBS)
	./a.out

gcov_report: tests
	gcovr --html-details coverage.html
	open coverage.html

style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c
	clang-format -n *.c
	rm .clang-format

install:
	mkdir -p build
	qmake6 calculator/calculator.pro -o build/Makefile
	cd build; make > /dev/zero 2> /dev/zero
	mkdir -p ~/Applications ; cp -r build/Calculator.app ~/Applications/Calculator.app


uninstall:
	rm -rf build
	rm -rf ~/Applications/Calculator.app

dist:
	cd .. && tar -czvf SmartCalc_v1.0.tar src

clean:
	rm -rf *o *a *out *css *html SmartCalc_v1.0_test.c build*

dvi:
	cd calculator && open dvi.html
