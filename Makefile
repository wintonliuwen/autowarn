CC = gcc

all:autowarn

autowarn: autowarn.o conf.o pdatas.o check.o log.o
	$(CC) -g $^ -ljansson -o $@

clean:
	rm -f *.o
	rm -f autowarn
