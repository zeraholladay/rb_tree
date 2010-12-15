CC=gcc 
CFLAGS=-Wall
CFILES=rb_tree.c lx_tree.c
OBJS=$(CFILES:.c=.o)

all: $(OBJS)
	@echo Fin

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	-rm *~ $(OBJS) 
