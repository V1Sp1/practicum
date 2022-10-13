#include <stdio.h>
#include <stdlib.h>

typedef struct inode {
    char *data;
    struct inode *next;
}inode;

typedef inode *list;

list xor_cpy_list(list l1, list l2)
{
    list l3, buff;
    if (l1 == NULL){
        buff = l1;
        l1 = l2;
        l2 = buff;
    }
    if (l1 == NULL){
        l3 = NULL;
        return l3;
    }
    l3 = (list)malloc(sizeof(inode));
    buff =l3;
    for(; l1 -> next != NULL; l1 = l1 -> next){
        buff -> data = l1 -> data;
        buff = buff -> next;
        buff = (list)malloc(sizeof(inode));
    }
    buff -> data = l1 -> data;
    buff -> next = NULL;
    for(; l2 != NULL; l2 = l2 -> next){
        buff = l3;
        for (;buff != NULL; buff = buff -> next){
            if (buff -> data == l2 -> data){
                break;
            }
        }
        if (buff == NULL){
            buff = (list)malloc(sizeof(inode));
            buff -> data = l2 -> data;
        }
    }
    return l3;
}
