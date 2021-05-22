CC      = g++
CFLAGS  = -std=gnu++17 -Wall -Wextra -O2 -DONLINE_JUDGE -I/opt/boost/gcc/include -I/opt/ac-library
LDFLAGS = -L/opt/boost/gcc/lib
LIBS    =
OBJS    = main.o
PROGRAM = a.out

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

%.o:		%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o *~ $(PROGRAM)
