#include <stdio.h>
#include <stdlib.h>

typedef struct inode {
    double *data;
    struct inode *next;
} inode;

typedef inode *list;

void swap_fst_lst(list *l)
{
    if ((*l == NULL) || ((*l) -> next == NULL)){
        return;
    }
    list buff = *l, last;
    for (; buff -> next -> next != NULL; buff = buff -> next);
    last = buff -> next;
    last -> next = (*l) -> next;
    (*l) -> next = NULL;
    buff -> next  = *l;
    *l = last;
}

void del_fst_occur(list *l, double *el)
{
    if (*l == NULL){
        return;
    }
    for (; (*l != NULL) && ((*l) -> data != el); l = &((*l) -> next));
     if (*l == NULL){
        return;
    }
    list buff = *l;
    (*l) = (*l) -> next;
    free(buff);
}

void hdel_fst_occur(list l, double *el)
{
    if (l == NULL){
        return;
    }
    for (; (l != NULL) && (l -> data != el); l = l -> next);
    if (l == NULL){
        return;
    }
    list buff = l;
    l = l -> next;
    free(buff);
}

void del_elem(list *l, double *el)
{
    if (*l == NULL){
        return;
    }
    while (*l != NULL){
        for (;(*l != NULL) && ((*l) -> data != el); l = &((*l) -> next));
        if (*l == NULL){
            return;
        }
        list buff = *l;
        *l = (*l) -> next;
        free(buff);
    }
}

void hdel_elem(list l, double *el)
{
    if (l == NULL){
        return;
    }
    while (l != NULL){
        for (;(l != NULL) && (l -> data != el); l = l -> next);
        if (l == NULL){
            return;
        }       
        list buff = l;
        l = l -> next;
        free(buff);
    }
}

void double_el(list *l, double *el)
{
    if (*l == NULL){
        return;
    }
    while (*l != NULL){
        for (;(*l != NULL) && ((*l) -> data != el); l = &((*l) -> next));
        if (l == NULL){
            return;
        }
        list buff = (list)malloc(sizeof(inode));
        buff -> data = el;
        buff -> next = (*l) -> next;
        (*l) -> next = buff;
    } 
}

void add_node(list *l, double *value)
{
    list new = (list)malloc(sizeof(inode));
    new -> data = value;
    new -> next = *l;
    *l = new;
}

void print_list(list *l)
{
    for (;(*l != NULL); l = &((*l) -> next)){
        printf("%3.1f ", *((*(*l)).data));
    }
    printf("\n");
}

int main(void)
{
    list l = NULL;
    double val[] = {1.0, 2.0, 2.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0, 4.0};
    add_node(&l, &val[0]);
    add_node(&l, &val[1]);
    add_node(&l, &val[2]);
    add_node(&l, &val[3]);
    add_node(&l, &val[4]);
    add_node(&l, &val[5]);
    add_node(&l, &val[6]);
    add_node(&l, &val[7]);
    add_node(&l, &val[8]);
    add_node(&l, &val[9]);
    print_list(&l);
    swap_fst_lst(&l);
    print_list(&l);
    del_elem(&l, &val[3]);
    print_list(&l);
    return 0;
}
