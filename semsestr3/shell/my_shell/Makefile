CC = gcc
CFLAGS= -g -Wall

myshell: solution.c errors.o parser.o scanner.o command.o runner.o runner.h errors.h command.h parser.h
	$(CC) $(CFLAGS) solution.c errors.o runner.o parser.o scanner.o command.o -o $@
errors.o: errors.h errors.c
	$(CC) $(CFLAGS) -c $< -o $@
parser.o: parser.h parser.c scanner.h
	$(CC) $(CFLAGS) -c $< -o $@
scanner.o: scanner.h scanner.c
	$(CC) $(CFLAGS) -c $< -o $@
command.o: command.h command.c
	$(CC) $(CFLAGS) -c $< -o $@
runner.o: runner.h runner.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o solution
val:
	valgrind  --leak-check=full --show-leak-kinds=all ./solution

.PHONY: clean
