FLAGS=-ggdb -Wall -Wextra -pedantic -std=c99
FILES=./src/main.c
INCLUDE=-I ./src/

all:
	gcc $(FLAGS) $(FILES)

clean:
	rm *.out
	rm *.o
