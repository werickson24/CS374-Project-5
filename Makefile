main: main.c llist.c
	gcc -Wall -Wextra -g -o main main.c

clean:
	rm -f main
