CC := g++
CFLAGS := -Wall -Wextra -std=c++11
TARGET := ./bin/main.out

all: run

src/main.lex.yy.c: src/main.l
	flex --noyywrap -o src/main.lex.yy.cpp src/main.l

src/main.tab.c: src/main.y
	bison -o src/main.tab.cpp --defines=src/main.tab.h -v src/main.y

src/pch.h.gch: src/pch.h
	g++ -x c++-header -o src/pch.h.gch -c src/pch.h

lex: src/main.lex.yy.c

yacc: src/main.tab.c

main: src/pch.h.gch
	$(CC) $(CFLAGS) $(shell ls ./src/structure/*.cpp ./src/*.cpp) -o ./bin/main.out

.PHONY: all clean main run lex yacc test debug link testscope asm nasm example-code out

run: lex yacc main

clean: 
	rm -f src/*.output src/main.lex.yy.cpp src/main.tab.cpp src/main.tab.h src/pch.h.gch $(TARGET) *.o ./bin/*

idt:
	./bin/main.out tests/idt.c > ./out/idt.txt

test:
	gcc -m32 ./out/test.s -o ./out/test.out
	qemu-i386 ./out/test.out

test5:
	./bin/main.out tests/test_lab5.c > ./out/test_lab5.txt

test6:
	./bin/main.out tests/test_lab6.c > ./out/test_lab6.txt

qxr:
	./bin/main.out tests/idt.c > ./out/idt.txt
	gcc -m32 ./out/test.s -o ./out/test.out
	qemu-i386 ./out/test.out