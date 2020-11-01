.PHONY:lcc, clean
lcc:
	flex -+ sysy.l
	g++ lex.yy.cc -o lcc.out
	./lcc.out
clean:
	rm *.out
