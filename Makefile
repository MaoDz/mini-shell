EXEC = main

all: $(EXEC)

main: main.o shell.o advanced.o utile.o
	gcc -Wall -o main main.o shell.o advanced.o utile.o -g

main.o : main.c shell.h advanced.h utile.h
	gcc -Wall -c main.c -g

shell.o : shell.c utile.h
	gcc -Wall -c shell.c -g

advanced.o : advanced.c utile.h
	gcc -Wall -c advanced.c -g

utile.o : utile.c utile.h
	gcc -Wall -c utile.c -g

#règles suplémentaires
clean :
	rm -f *.o *~ *.txt $(EXEC)

