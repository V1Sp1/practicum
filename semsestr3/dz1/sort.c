#include <stdio.h>

void bubble(int *ar, int len)
{
    int i, j, buff;
    for (i = 0; i < len - 1; i++){
        for (j = i + 1; j < len; j++){
            if (ar[i] > ar[j]){
                buff = ar[j];
                ar[j] = ar[i];
                ar[i] = buff;
            }
        }
    }
}

void insert(int *ar, int len)
{
    int i, j, buff;
    for (i = 1; i < len; i++){
        buff = ar[i];
        for (j = i - 1; (buff <= ar[j]) && (j >= 0); j--){
            ar[j+1] = ar[j];
        }
        ar[j+1] = buff;
    }
}

void qsort(int *ar, int len)
{   
    if (len < 2){
        return;
    }
    int mid = ar[len / 2], l = 0, r = len - 1; // left and right
    while (l < r){
        while ((l < len) && (ar[l] < mid)){
            l++;
        }
        while ((r > 0) && (ar[r] >= mid)){
            r--;
        }
        if (l < r){
            int buff;
            buff = ar[r];
            ar[r] = ar[l];
            ar[l] = buff;
        }
    }
    if (l == r){
        l++;
        int buff;
        buff = ar[r];
        ar[r] = ar[l];
        ar[l] = buff;
    }
    if (l >= r){
        qsort(&ar[0],r + 1);
        qsort(&ar[l], len - l);
    }
}

int main(void)
{
    int m[] = {3, 4, 1, 5, 8, 13, 7 , 34, 0};
    qsort(m, sizeof(m) / sizeof(*m));
    int i;
    for (i = 0; i < sizeof(m) / sizeof(*m); i++){
        printf("%d ", m[i]);
    }
    printf("\n");
    return 0;
}
