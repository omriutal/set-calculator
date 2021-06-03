CC = gcc
OBJS = myset.o set.o analyze.o massages.o
EXEC = myset
DEBUG_FLAG = -g
COMP_FLAG = -Wall -ansi -pedantic $(DEBUG_FLAG)

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

myset.o: myset.c set.h analyze.h massages.h
	$(CC) -c $(COMP_FLAG) $*.c

set.o: set.c set.h massages.h
	$(CC) -c $(COMP_FLAG) $*.c

analyze.o: analyze.c analyze.h massages.h
	$(CC) -c $(COMP_FLAG) $*.c

massages.o: massages.c massages.h
	$(CC) -c $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS)
