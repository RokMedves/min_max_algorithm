CC=g++
COMMONFLAGS= -g
CFLAGS= -std=c++17 -Wall -w $(COMMONFLAGS)
OFLAGS= $(COMMONFLAGS) -c
OBJS=main.o board.o bot.o
EXE=output


$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)


main.o: main.cpp
	$(CC) $(OFLAGS) main.cpp

board.o: board.cpp
	$(CC) $(OFLAGS) board.cpp

bot.o: bot.cpp
	$(CC) $(OFLAGS) bot.cpp

clean:
	rm *.o output

cleanEmacs:
	rm *~
run: $(EXE)
	./output

redo: 
	make clean
	make run
