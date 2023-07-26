make:
	gcc -std=c17 -o c3 -g c3.c

clean:
	rm -f c3

run: clean make
	exec ./c3

scratch:
	rm -rf scratch
	gcc -std=c17 -o scratch -g scratch.c
	exec ./scratch