#include "queue42.h"

void putqu(queue *q, void *value)
{
    queue new;
    new -> data = data;
    new -> next = NULL;
    if (*q == NULL){
        *q = new;
    }
    for (; (*q) -> next != NULL; q = &((*q) -> next));
    (*q) -> next = new;
}

void *getqu(queue *q)
{
    if (*q == NULL){
        return NULL;
    }
    queue fo = *q;
    void *value = fo -> data;
    *q = (*q) -> next;
    free(fo);
    return value;
}

int sizequ(queue q)
{
    int n = 0;
    for(; q != NULL; q = q -> next){
        ++n;
    }
    return n;
}

void clearqu(queue *q)
{
    queue del = *q;
    for(; *q != NULL; *q = (*q) -> next){
        free(del);
        del = (*q) -> next;
    }
}
