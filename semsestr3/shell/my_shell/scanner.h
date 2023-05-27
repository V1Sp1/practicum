#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum TokenKind
{
    T_EOF,
    T_NEWLINE,
    T_OPEN,
    T_CLOSE,
    T_SEQ,
    T_CONJ,
    T_BACK,
    T_DISJ,
    T_PIPE,
    T_IN,
    T_APPEND,
    T_OUT,
    T_WORD
};

typedef struct Token
{
    enum TokenKind kind;
	int capacity;
    char *text;
    int len;
}Token;

int init_scanner(FILE *f);
void free_scanner(void);
int next_token(Token *token);
void free_token(Token *token);

#endif
