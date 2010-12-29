CC=gcc 
CFLAGS=-Wall
CFILES=rb_tree.c lx_tree.c hash.c strsave.c
OBJS=$(CFILES:.c=.o)
OUTLIB=libdict.so

all: $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(OUTLIB) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

example: example.c
	make
	$(CC) $(CFLAGS) example.c -L. -ldict -o example

clean:
	-rm *~ $(OBJS) $(OUTLIB) example
