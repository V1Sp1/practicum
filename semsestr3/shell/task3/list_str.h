#ifndef LIST_STR_H_TASK3
#define LIST_STR_H_TASK3

#include <stdio.h>
#include <stdlib.h>

#define SIZE 64
/*
int c; //  current symbol
char **lst; // list of words (as an array)
int sizelist; // word list size
int curlist; // index of the current word in the list
char *word; // buffer for accumulating the current word
int sizeword; // size of current word
int curword; // index of current symbol in the word
*/

//frees the memory allocated for the list
void clearlist(int *sizelist, int *curlist, char ***lst);

//nullifies the list and associated variables
void nulllist(int *sizelist, int *curlist, char ***lst);

//terminate the list and aligns its width
void termlist(int *sizelist, int *curlist, char ***lst);

//nullifies array for current word and associated variables
void nullword(int *sizeword, int *curword, char **word);

//reads the next characters from the buffer, if the buffer
//is processed? then reads the next 10 characters into it
int getsym();

//adds the next characters to the current word
void addsym(int *sizeword, int *curword, char **word, int c);

//adds another word to the end of the list
void addword(int *sizeword, int *curword, char **word,
             int *sizelist, int *curlist, char ***lst);

//prints all the words in the list separated by \t
void printlist(char **lst);

//sort the list in lexicographic order
void insertsort(char **ar, int len);

//checks if a character is a special character
int symset(int c);


#endif /* LIST_STR_H_TASK3 */
