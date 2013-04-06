CC = gcc
CFLAGS= -O2 -g -Wall -pg

SUFFIXES= .c .o

CFLAGS+= -DTEST_SHORT
CFLAGS+= -DTEST_CHECK

OBJECTS= gol.o

PROGS= gol

all: $(PROGS)

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

remote_proxy: gol.o
	$(CC) $(CFLAGS) gol.o $(LDFLAGS) -o gol
	@echo "program built ... OK!"

clean:
	rm -f $(OBJECTS) $(PROGS) gmon.out
