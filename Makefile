all:	stringProg
stringProg: main.o my_string.a my_string.h
	gcc -Wall -g -o stringProg main.o my_string.a
my_string: my_string.a
my_string.a: my_string.o 
	ar -rcs my_string.a my_string.o
my_string.o: my_string.c my_string.h
	gcc -Wall -g -c my_string.c 
main.o: main.c my_string.h
	gcc -Wall -g -c main.c 

.PHONY: clean#.PHONY means that clean is not a file.
clean:
	rm -f *.o *.a  stringProg
