#include <stdio.h>
#include <stdlib.h>
#include "list_str.h"

int main(void)
{
    typedef enum {
        Start,
        Mkword,
        Sep,
        DoubleSep,
        Newline,
        Stop
    } vertex;
    vertex V=Start;
    int c; //  current symbol
    char **lst; // list of words (as an array)
    int sizelist; // word list size
    int curlist; // index of the current word in the list
    char *word; // buffer for accumulating the current word
    int sizeword; // size of current word
    int curword; // index of current symbol in the word
    c = getsym();
    nulllist(&sizelist, &curlist, &lst);
    while(1 == 1) switch(V){
        case Start:
            if((c == ' ') || (c == '\t')){
                c = getsym();
            } else if (c == EOF) {
                nullword(&sizeword, &curword, &word);
                termlist(&sizelist, &curlist, &lst);
                printlist(lst);
                clearlist(&sizelist, &curlist, &lst);
                V = Stop;
            } else if (c == '\n') {
                termlist(&sizelist, &curlist, &lst);
                printf("original string:\n");
                printlist(lst);
                insertsort(lst, sizelist - 1);
                printf("sorted string:\n");
                printlist(lst);
                V = Newline;
                c = getsym();
            } else {
                nullword(&sizeword, &curword, &word);
                addsym(&sizeword, &curword, &word, c);
                int c1 = c;
                if (!symset(c)){
                    V = Sep;
                } else {
                    V = Mkword;
                }
                c = getsym();
                if (c == c1 && (c == '>' || c == '|' || c == '&')){
                    V = DoubleSep;
            }
            break;
        case Mkword:
             if(symset(c)) {
                addsym(&sizeword, &curword, &word, c);
                c = getsym();
            } else {
                V = Start;
                addword(&sizeword, &curword, &word, &sizelist, &curlist, &lst);
            }
            break;
        case Sep:
            V = Start;
            addword(&sizeword, &curword, &word, &sizelist, &curlist, &lst);
            }
            break;
        case DoubleSep:
            V = Start;
            addsym(&sizeword, &curword, &word, c);
            addword(&sizeword, &curword, &word, &sizelist, &curlist, &lst);
            c = getsym();
            break;
        case Newline:
            clearlist(&sizelist, &curlist, &lst);
            V = Start;
            break;
        case Stop:
            exit(0);
            break;
    }
    return 0;
}
