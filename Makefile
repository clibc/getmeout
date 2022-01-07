FLAGS=-ggdb -Wall -Wextra -pedantic -std=c99
FILES=./src/main.c
INCLUDE=-I ./src/

all:
	gcc $(FLAGS) $(FILES)

nasm:
	nasm -felf64 output.asm
	ld -o output.out output.o

clean:
	rm *.out
	rm *.o
