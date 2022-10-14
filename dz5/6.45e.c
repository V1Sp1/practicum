#include "tree45e.h"

int count_level_tree(tree tr, int number)
{
    if ((number < 0) || (tr == NULL)){
        return 0;
    }
    int n, last = 1, next = 0;
    queue q = NULL;
    putqu(&q, tr);
    for(n = 0; n < number; ++n){
        tree buff;
        for(; last > 0; --last){
            buff = (tree)getqu(q);
            if (buff -> left != NULL){
                ++next;
                putqu(q, buff -> left);
            }
            if (buff -> right != NULL){
                ++next;
                putqu(q, buff -> right);
            }
        }
        last = next;
        next = 0;
    }
    clearqu(&q);
    return last;
}

void printqu(queue q)
{
    for(; q != NULL; q = q -> next){
        printf("%d ", ((tree)(q -> data)) -> data);
    }
    printf("\n");
}

void printtr(tree tr)
{
    int last = 1, next = 0;
    queue q = NULL;
    putqu(&q, tr);
    for(;;){
        tree buff;
        for(; last > 0; --last){
            buff = (tree)getqu(q);
            if (buff -> left != NULL){
                ++next;
                printf("%d ", buff -> data);
                putqu(q, buff -> left);
            }
            if (buff -> right != NULL){
                ++next;
                putqu(q, buff -> right);
            }
        }
        if (next == 0){
            break;
        }
        printf("\n");
        last = next;
        next = 0; 
    }
}

void addtr(tree *tr, int value)
{
    if (*tr == NULL){
        *tr = (tree)malloc(sizeof(tnode));
        (*tr) -> data = value;
        (*tr) -> left = NULL;
        (*tr) -> right = NULL;
        return;
    }
    if ((*tr) -> data > value){
        addtr(&((*tr) -> left), value);
    } else {
        addtr(&((*tr) -> right), value);
    }
}

void cleartr(tree *tr)
{
    if (*tr == NULL){
        return;
    }
    cleartr(&((*tr) -> left));
    cleartr(&((*tr) -> right));
    free(*tr);
}

int main(void)
{
    tree tr = NULL;
    addtr(&tr, 1);
    addtr(&tr, 2);
    addtr(&tr, 3);
    addtr(&tr, 4);
    addtr(&tr, 5);
    printtr(tr);
    printf("--------------\n");
    cleartr(&tr);
    return 0;
}
