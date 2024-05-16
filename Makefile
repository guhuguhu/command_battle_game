CC=g++
CFLAGS=-g
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
INCS=$(wildcard *.hpp)

game: $(OBJS)
	g++ -o  game $(OBJS) $(LDFLAGS)

$(OBJS): $(INCS) $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

test: game
	./test.sh

clean:
	rm -f game *.o *~ tmp*

.PHONY: test clean