all: expr.y
	make bison
	make gcc
	
bison: expr.y mtob.y
	bison -d expr.y
	bison -d mtob.y

clean:
	rm expr expr.tab.c expr.tab.h
	rm mtob mtob.tab.c mtob.tab.h

doe: expr
	./expr

dom: mtob
	./mtob

gcc: expr.tab.c
	gcc -o expr expr.tab.c
	gcc -o mtob mtob.tab.c