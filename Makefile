CC=g++
PROGRAM=main
SRC=main.cpp token.cpp syntax.cpp expr.cpp term.cpp opr.cpp symb.cpp
HEADER=types.h token.h syntax.h expr.h term.h opr.h	symb.h
DEBUG=-g -DDEBUG

$(PROGRAM): $(SRC) $(HEADER)
	$(CC) $(DEBUG) -o $(PROGRAM) $(SRC)

release: $(SRC) $(HEADER)
	$(CC) -o $(PROGRAM) $(SRC)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm *.o
