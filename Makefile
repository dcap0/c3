make:
	gcc -std=c17 -o c3 -g c3.c

clean:
	rm c3

run: clean make
	exec ./c3
