build: editor.o
	gcc editor.o -o editor

main: editor.c
	gcc -Wall -c editor.c

run: editor
	./editor

clean:
	rm -f editor.o
