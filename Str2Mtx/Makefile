
test: clean build
	gcc -g obj/strparser.o test/main.c -I include/ -o bin/test.exe
	bin/test.exe

build:
	mkdir bin obj
	gcc -g -c src/strparser.c -I include/ -o obj/strparser.o

clean:
	rm -rf bin obj