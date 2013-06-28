CC=g++
PROGRAM=main
SRC=main.cpp token.cpp syntax.cpp expr.cpp
HEADER=types.h token.h syntax.h expr.h
DEBUG=-g -DDEBUG

$(PROGRAM): $(SRC) $(HEADER)
	$(CC) $(DEBUG) -o $(PROGRAM) $(SRC)

release: $(SRC) $(HEADER)
	$(CC) -o $(PROGRAM) $(SRC)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm *.o
