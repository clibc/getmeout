FLAGS=-ggdb -Wall -Wextra -pedantic -std=c99
FILES=./src/main.c

all:
	gcc $(FLAGS) $(FILES)

clean:
	rm *.out
	rm *.o
