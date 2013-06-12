.PHONY: debug clean

PROGRAM	= main
CC		= g++
VPATH	= ./header
OBJECT	= main.o parse.o expression.o func.o data.o
OBJDST	= ./obj
HEADER	= main.h parse.h expression.h func.h data.h

$(PROGRAM): $(OBJECT) $(HEADER)
	$(CC) $(OBJDST)/*.o -o $(PROGRAM)

.cpp.o:
	$(CC) -o $(OBJDST)/$@ -c $<

vpath %.o ./obj

clean:
	@rm $(OBJDST)/*.o
