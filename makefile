all: dir.o
	gcc -o dir dir.o

dir.o: dir.c
	gcc -c dir.c

run:
	./dir

clean:
	rm *.o
	rm dir