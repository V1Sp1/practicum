#ifndef QUEUE6P42
#define QUEUE6P42
#include <stdlib.h>

typedef struct inode {
    void *data;
    struct inode *next;
} inode;

typedef inode *queue;

void putqu(queue *q, void *data);

void *getqu(queue *q);

int sizequ(queue q);

void clearqu(queue *q);
#endif
