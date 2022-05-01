all: main_editor setup run

main_editor: main_editor.c
	$(CC) -o main_editor main_editor.c -Wall -W -pedantic -std=c99

setup: setup.c
	gcc setup.c

run: a.out
	./a.out

clean:
	rm main_editor a.out
