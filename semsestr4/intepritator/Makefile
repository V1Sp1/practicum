C = g++
CFLAGS = -Wall -g
VFLAGS = --leak-check=full --show-leak-kinds=all

lex.o: lex.cpp lex.hpp
		$(CC) $(CFLAGS) -c $< -o $@

ident.o: ident.cpp ident.hpp lex.hpp #?
		$(CC) $(CFLAGS) -c $< -o $@

scanner.o: scanner.cpp scanner.hpp lex.hpp ident.hpp
		$(CC) $(CFLAGS) -c $< -o $@

lexer: lexer.cpp scanner.o ident.o lexem.o
		$(CC) $(CFLAGS) lexer.cpp scanner.o ident.o lex.o -o $@

interpret: 

clean:
		rm -f *.o lexer

val:
		valgrind $(VFLAGS) ./lexer
