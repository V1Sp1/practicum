CC = gcc
CFLAGS = -Wall

main_str: main_str.c list_str.o
	$(CC) $(CFLAGS) main_str.c list_str.o -o $@

list_str.o: list_str.c list_str.h
	$(CC) $(CFLAGS) -c $< -o $@

run: list_str
	./list_str

clean:
	rm -f *.o list_str
