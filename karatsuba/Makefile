CC=gcc

#results dumped by cilkview objects
VIEWS = main

CFLAGS= -std=gnu99 -Wall -O3 -fcilkplus
LDFLAGS= -ldl -lcilkrts
INCLUDES = -I/afs/csail.mit.edu/proj/courses/6.172/cilkutil/include

all: main

main : main.c poly.c poly.h temp_space.h
	$(CC) $(CFLAGS) $(INCLUDES) $@.c $(LDFLAGS) -o $@

OUTPUTS = $(VIEWS:%=%.csv) $(VIEWS:%=%.plt) $(ALLTARGETS:%=%.cv.out) cilkview.out

clean :
	rm -f main *~

