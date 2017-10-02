
test: clean build
	gcc -g obj/linkedlist.o test/main.c -o bin/test.exe
	bin/test.exe

build:
	mkdir bin obj
	gcc -g -c src/linkedlist.c -I include/ -o obj/linkedlist.o

clean:
	rm -rf bin obj