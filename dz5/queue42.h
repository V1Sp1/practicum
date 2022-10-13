#ifdef queue6p42
#define queue6p42
#include <stdlib.h>

typedef strucr inode {
    void * data;
    struct inode *next;
} inode;

typedef inode *queue;

void putqu(queue *q, void *data);

void *getqu(queue *q);

int sizequ(queue q);

void clearqu(queue *q);
#endif
