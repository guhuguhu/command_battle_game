CC=g++
CFLAGS=-g
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
INCS=$(wildcard *.hpp)

command_battle_game: $(OBJS)
	g++ -g -o command_battle_game $(OBJS) $(LDFLAGS)

$(OBJS): $(INCS) $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

clean:
	rm -f command_battle_game *.o *~ tmp*
