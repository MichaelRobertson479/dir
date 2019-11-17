all: infostat.o
	gcc -o infostat infostat.o

infostat.o: infostat.c
	gcc -c infostat.c

run:
	./infostat

clean:
	rm *.o
	rm infostat
	rm stat