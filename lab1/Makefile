s0: 0.cpp
	g++ -o 0.s -S -masm=att 0.cpp

s1: 1.c
	gcc -o 1.s -S -masm=att 1.c

out: 1.c
	gcc -o 1.out 1.s
	./1.out