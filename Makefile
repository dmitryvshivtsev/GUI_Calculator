.PHONY: all tests clean open

CFLAGS = -Wall -Werror -Wextra
CC = gcc


all:
	make tests

tests:
	@$(CC) $(CFLAGS) -lgtest -lstdc++ -std=c++17 Model/s21_model.cc tests/validation_tests.cc -o validation_tests.o
	@./validation_tests.o
	@$(CC) $(CFLAGS) -lgtest -lstdc++ -std=c++17 Model/s21_model.cc tests/calculator_tests.cc -o calculator_tests.o
	@./calculator_tests.o
	@echo "=== TESTS DONE ==="

clean:
	@rm -rf *.o *.out
	@echo "=== CLEAN DONE ==="

dvi:
	open info.texi

open:
	open build/View.app

check:
	@cp ../materials/linters/.clang-format .
	@clang-format -i Model/*.cc
	clang-format -n Model/*.cc
	@clang-format -i Controller/*.cc
	clang-format -n Controller/*.cc
	@clang-format -i View/*.cc
	clang-format -n View/*.cc
	@rm .clang-format
	@echo "=== STYLE CHECK DONE ==="

install:
	make uninstall
	mkdir build
	cd View && qmake && make && make clean && rm Makefile && cd ../ && mv View/View.app build

uninstall:
	rm -rf build

dist: install
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/src
	mv ./build/View.app Archive_SmartCalc_v2.0/src/
	tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	rm -rf Archive_SmartCalc_v2.0/
	rm -rf build
