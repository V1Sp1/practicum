#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_str.h"

void clearlist(int *sizelist, int *curlist, char ***lst )
{
    int i;
    *sizelist = 0;
    *curlist = 0;
    if (*lst == NULL){
        return;
    }
    for (i = 0; (*lst)[i] != NULL; ++i){
        free((*lst)[i]);
    }
    free(*lst);
    *lst = NULL;
}

void nulllist(int *sizelist, int *curlist, char ***lst)
{
    *sizelist = 0;
    *curlist = 0;
    *lst = NULL;
}

void termlist(int *sizelist, int *curlist, char ***lst)
{
    if (*lst == NULL){
        return;
    }
 //
    *sizelist = *curlist + 1;
    *lst = realloc(*lst, (*sizelist) * sizeof(char*));
    (*lst)[*curlist] = NULL;
}

void nullword(int *sizeword, int *curword, char **word)
{
    *word = NULL;
    *sizeword = 0;
    *curword = 0;
}

int getsym()
{
    static char buff[10];
    static int curbuff = 0;
    static int sizebuff = 0;
    if ((curbuff == 0) || (curbuff == sizebuff)){
        curbuff = 0;
        sizebuff = 0;
        if (fscanf(stdin, "%10[^\n]%n", buff, &sizebuff) == EOF){
            return EOF;
        }
        if (sizebuff != 10){
            buff[sizebuff] = '\n';
            fscanf(stdin, "%*c");
            ++sizebuff;
        }
    }
    ++curbuff;
    return buff[curbuff - 1];
}

void addsym(int *sizeword, int *curword, char **word, int c)
{
    if (*curword > *sizeword - 1){
        *sizeword += SIZE;
        *word = realloc(*word, *sizeword); //
    }
    (*word)[*curword] = c;
    ++(*curword);
}

void addword(int *sizeword, int *curword, char **word,
             int *sizelist, int *curlist, char ***lst)
{
 //
    *sizeword = *curword + 1;
    (*word) = realloc((*word), (*sizeword));
    (*word)[*curword] = '\0';
    if (*curlist > (*sizelist) - 1){
        (*sizelist) += SIZE;
        (*lst) = realloc(*lst, (*sizelist) * sizeof(char*)); //
    }
    (*lst)[(*curlist)] = *word;
    ++(*curlist);
}

void printlist(char **lst)
{
    int i;
    if (lst == NULL){
        return;
    }
    for (i = 0; lst[i] != NULL; ++i){
        printf("%s\t", lst[i]);
    }
    printf("\n");
}

void insertsort(char **ar, int len)
{
    int i, j;
    char *buff;
    for (i = 1; i < len; ++i){
        buff = ar[i];
        for (j = i; (j > 0) && (strcmp(buff, ar[j - 1]) < 0); --j){
            ar[j] = ar[j - 1];
        }
        ar[j] = buff;
    }
}

int symset(int c){
    return c != '\n' &&
           c != '\t' &&
           c != ' ' &&
           c != '>' &&
           c != '<' &&
           c != '&' &&
           c != '|' &&
           c != ';' &&
           c != '(' &&
           c != ')' &&
           c !=  EOF ;
} 
